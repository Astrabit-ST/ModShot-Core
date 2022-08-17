physfs = dependency('physfs', version: '>=2.1', static: build_static)
sdl2 = dependency('SDL2', static: build_static)
freetype = dependency('freetype2', static: build_static)
harfbuzz = dependency('harfbuzz', static: build_static)
sdl2_ttf = dependency('SDL2_ttf', static: build_static)
sdl2_image = dependency('SDL2_image', static: build_static)
sigcxx = dependency('sigc++-2.0', static: build_static)
pixman = dependency('pixman-1', static: build_static)
png = dependency('libpng', static: build_static)
jpeg = dependency('libjpeg', static: build_static)
tiff = dependency('libtiff-4', static: build_static)
webp = dependency('libwebp', static: build_static)
zlib = dependency('zlib', static: build_static)
nsgif = dependency('libnsgif', static: build_static)

fmod_arch_prefix = ''
if host_system == 'windows'
	fmod_arch_prefix = 'x64'
else
	fmod_arch_prefix = 'x86_64'
endif

if fmod
	# FUck
	fmod_lib_path = get_option('fmod_core_lib_dir')
	if fmod_lib_path == ''
	  fmod_lib_path = join_paths(
		meson.global_source_root(), 'fmod/api/core/lib/' + fmod_arch_prefix
	  )
	endif

	fsbank_lib_path = get_option('fmod_fsbank_lib_dir')
	if fsbank_lib_path == ''
	  fsbank_lib_path = join_paths(
		meson.global_source_root(), 'fmod/api/fsbank/lib/' + fmod_arch_prefix
	  )
	endif

	studio_lib_path = get_option('fmod_studio_lib_dir')
	if studio_lib_path == ''
	  studio_lib_path = join_paths(
		meson.global_source_root(), 'fmod/api/studio/lib/' + fmod_arch_prefix
	  )
	endif

	fmod_lib = compilers['cpp'].find_library('fmod', dirs: fmod_lib_path)
	fsbank = compilers['cpp'].find_library('fsbank', dirs: fsbank_lib_path)
	studio = compilers['cpp'].find_library('fmodstudio', dirs: studio_lib_path)
	global_dependencies += [fmod_lib, fsbank, studio]
else
	# FMOD does not require these libraries
	openal = dependency('openal')
	vorbisfile = dependency('vorbisfile', static: build_static)
	vorbis = dependency('vorbis', static: build_static)
	ogg = dependency('ogg', static: build_static)
	sdl_sound = dependency('SDL2_sound', static: build_static)
	global_dependencies += [openal, vorbisfile, vorbis, ogg, sdl_sound]
endif

if host_system == 'windows'
	bz2 = dependency('bzip2')
	iconv = compilers['cpp'].find_library('iconv')
else
	bz2 = compilers['cpp'].find_library('bz2')
	iconv = compilers['cpp'].find_library('iconv')
	gtk = dependency('gtk+-3.0')
	xfconf = dependency('libxfconf-0')
	global_dependencies += [gtk, xfconf]
endif

# Windows needs to be treated like a special needs child here
# Windows is a special needs child
explicit_libs = ''
if host_system == 'windows'
    # Newer versions of Ruby will refuse to link without these
    explicit_libs += 'libmsvcrt;libgcc;libmingwex;libgmp;'
endif

foreach l : explicit_libs.split(';')
        if l != ''
            global_link_args += '-l:' + l + '.a'
        endif
endforeach

global_include_dirs += include_directories('.',
    'filesystem/headers',
    'graphics/headers',
    'input/headers',
    'modshot/headers',
    'oneshot/headers',
    'opengl/headers',
    'rgss/headers',
    'thread/headers',
    'util/headers'
)

global_dependencies += [bz2, zlib, sdl2, pixman, physfs, iconv, sdl2_ttf, sigcxx, sdl2_image, png, jpeg, nsgif, freetype, tiff, webp, harfbuzz]

if host_system == 'windows'
    global_dependencies += compilers['cpp'].find_library('wsock32')
    global_dependencies += compilers['cpp'].find_library('winmm')
    global_dependencies += compilers['cpp'].find_library('Secur32')
    global_dependencies += compilers['cpp'].find_library('Shlwapi')
    global_dependencies += compilers['cpp'].find_library('gdiplus')
endif

main_source = files(
	'filesystem/source/filesystem.cpp',
	'graphics/source/autotiles.cpp',
	'graphics/source/bitmap.cpp',
	'graphics/source/graphics.cpp',
	'graphics/source/font.cpp',
	'graphics/source/sprite.cpp',
	'graphics/source/scene.cpp',
	'graphics/source/tilemap.cpp',
	'graphics/source/tileatlas.cpp',
	'graphics/source/window.cpp',
	'graphics/source/viewport.cpp',
	'graphics/source/plane.cpp',
	'input/source/input.cpp',
	'input/source/keybindings.cpp',
	'input/source/settingsmenu.cpp',
	'opengl/source/glstate.cpp',
	'opengl/source/gl-debug.cpp',
	'opengl/source/gl-fun.cpp',
	'opengl/source/gl-meta.cpp',
	'opengl/source/shader.cpp',
	'opengl/source/texpool.cpp',
	'opengl/source/vertex.cpp',
	'opengl/source/tilequad.cpp',
	'modshot/source/display.cpp',
	'oneshot/source/screen.cpp',
	'oneshot/source/oneshot.cpp',
	'oneshot/source/i18n.cpp',
	'rgss/source/table.cpp',
	'rgss/source/etc.cpp',
	'thread/source/eventthread.cpp',
	'thread/source/sharedstate.cpp',
	'util/source/algorithm.cpp',
	'util/source/config.cpp',
	'util/source/win-consoleutils.cpp',
	'main.cpp'
)

global_sources += main_source

if steam == true
    global_sources += files(
        'steam/steam.cpp',
        '../steamshim/steamshim_child.c'
    )
    global_include_dirs += include_directories(
        'steam',
        '../steamshim'
    )

    global_args += '-DSTEAM'
endif

if fmod
	global_args += '-DUSE_FMOD'
else
	global_include_dirs += include_directories('al/headers')
	global_sources += files(
		    'al/source/alstream.cpp',
			'al/source/audiostream.cpp',
			'al/source/audiochannels.cpp',
			'al/source/audio.cpp',
			'al/source/soundemitter.cpp',
			'al/source/sdlsoundsource.cpp',
			'al/source/vorbissource.cpp',
	)
endif

if host_system == 'windows'
    global_sources += files('modshot/source/notifications_win32.cpp')
else
    global_sources += files('oneshot/source/xdg-user-dir-lookup.c')
    global_sources += files('modshot/source/notifications_unix.cpp')
endif
