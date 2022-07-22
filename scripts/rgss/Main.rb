#==============================================================================
# ** Main
#------------------------------------------------------------------------------
#  After defining each class, actual processing begins here.
#==============================================================================

at_exit do
  Wallpaper.reset
  save unless $game_switches[99] || ($game_system.map_interpreter.running? || !$scene.is_a?(Scene_Map))
end

module Audio
  class << self
    def method_missing(*args)
    end
  end

end

module FMODPlayer

  def self.start
    $evinst.start
    $fmod.update
  end

  def self.stop
    $evinst.stop(0)
    $fmod.update
  end

  def self.set(param, value, ignoreseek = false)
    $evinst.set_parameter_by_name(param, value, ignoreseek)
    $fmod.update
  end

end

begin
  $console = Graphics.fullscreen
  Graphics.frame_rate = 60
  Font.default_size = 20

  fresult, $fmod = FMOD::Studio::System.new(32, 1, 0)

  warn "FMOD Result: #{fresult} | System: #{$fmod} | Valid?: #{$fmod.is_valid}"

  fresult, $bank = $fmod.load_bank_file("Audio/Banks/Master.bank", 0)
  fresult, $bgmbank = $fmod.load_bank_file("Audio/Banks/BGMs.bank", 0)
  fresult, $ambbank = $fmod.load_bank_file("Audio/Banks/Ambients.bank", 0)
  fresult, $strbank = $fmod.load_bank_file("Audio/Banks/Master.strings.bank", 0)

  $fmod.update

  fresult, $evdesc = $fmod.get_event("event:/BGMs/BGM01")
  fresult, $evinst = $evdesc.create_instance

  $fmod.update

  FMODPlayer.start
  FMODPlayer.set("bgm_progression", 0.0)

  # Load persistent data
  Persistent.load

  # Prepare for transition
  Graphics.freeze
  $demo = false
  $GDC = false
  # Make scene object (title screen)
  $scene = Scene_Title.new
  Oneshot.allow_exit false
  Oneshot.exiting false

  #  x = Oneshot.textinput("Foo Bar")
  #  print("#{x}")

  # Call main method as long as $scene is effective
  while $scene != nil
    $scene.main
  end
  # Fade out
  Oneshot.exiting true
  Graphics.transition(20)

  if Journal.active?
    Journal.set ""
  end

  Oneshot.allow_exit true
rescue Errno::ENOENT
  # Supplement Errno::ENOENT exception
  # If unable to open file, display message and end
  filename = $!.message.sub("No such file or directory - ", "")
  print("Unable to find file #{filename}.")
end
