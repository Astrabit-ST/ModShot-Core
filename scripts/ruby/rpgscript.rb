#!/usr/bin/ruby
require "zlib"
require "optparse"

game_dir = nil
output = nil
extract = false
scripts_dir = nil

options = OptionParser.new do |opts|
  opts.banner = "Usage: rpgscript.rb [options]"

  opts.on("-e", "--extract", "Extract scripts") do
    extract = true
  end

  opts.on("-g", "--game-dir DIR", String, "Game directory (incompatible with output)") do |dir|
    game_dir = dir

    if output
      puts opts
      exit 1
    end
  end

  opts.on("-o", "--output FILE", String, "Output file (incompatible with game dir)") do |file|
    output = file

    if game_dir
      puts opts
      exit 1
    end
  end

  opts.on("-s", "--scripts-dir DIR", String, "Scripts directory") do |dir|
    scripts_dir = dir
  end

  opts.on_tail("-h", "--help", "Show this message") do
    puts opts
    exit
  end
end
options.parse!

unless scripts_dir && (game_dir || output)
  puts "Incompatible options"
  puts options
  exit 1
end

target_path = nil
unless output
  # Determine version of game engine
  game_data_dir = File.join(game_dir, "Data")
  unless Dir.exist? game_data_dir
    STDERR.puts "warning: #{game_dir} does not have a Data subdirectory"
    game_data_dir = game_dir
  end

  Dir.entries(game_data_dir).each do |e|
    ext = File.extname(e)
    if ext =~ /\.r[xv]data2?/
      target_path = File.join(game_data_dir, "xScripts" + ext)
      break
    end
  end

  unless target_path
    STDERR.puts "warning: could not determine game engine version, assuming XP"
    target_path = File.join(game_data_dir, "xScripts.rxdata")
  end
else
  target_path = output
end

# Generate path of script list
list_path = File.join(scripts_dir, "_scripts.txt")

if extract
  # Make sure the script directory exists
  Dir.mkdir(scripts_dir) unless Dir.exists? scripts_dir

  # Keep track of names of scripts extracted so we can warn about duplicates
  names = Hash.new(0)

  # Read scripts
  File.open(target_path, "rb") do |fin|
    File.open(list_path, "w") do |flist|
      Marshal.load(fin).each_with_index do |script, index|
        name = script[1].strip
        data = Zlib::Inflate.inflate(script[2]).rstrip
          .gsub(/[ \t]*(?:$|\r\n?)/, "\n")

        # Make sure this file doesn't already exist
        if name.empty?
          if data.empty? || data == "\n"
            flist.puts
            next
          else
            name = "UNTITLED"
          end
        end

        names[name] += 1
        if names[name] > 1
          name << " (#{names[name]})"
        end

        if data.empty? || data == "\n"
          # Treat this like a comment
          flist.puts("# " + name)
        else
          # Write to file order list
          flist.puts(name)

          # Write script file
          File.open(File.join(scripts_dir, name + ".rb"), "wb") do |fout|
            fout.write(data)
          end
        end
      end
    end
  end
  puts "#{target_path} extracted."
else
  # Write scripts
  scripts = []

  IO.foreach(list_path) do |name|
    name.strip!
    next if name.empty? || name.start_with?("#")

    data = File.read(File.join(scripts_dir, name + ".rb")).rstrip.gsub("\n", "\r\n")

    script = Array.new(3)
    script[0] = 0
    script[1] = name
    script[2] = Zlib.deflate(data)
    scripts << script
  end

  File.open(target_path, "wb") { |f| f.write(Marshal.dump(scripts)) }
  puts "#{target_path} written."
end
