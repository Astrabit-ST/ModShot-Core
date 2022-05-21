boost = dependency('boost', version: '>=1.49', modules: ['program_options'], static: build_static)
physfs = dependency('physfs', version: '>=2.1', static: build_static)
openal = dependency('openal')
vorbisfile = dependency('vorbisfile', static: build_static)
vorbis = dependency('vorbis', static: build_static)
ogg = dependency('ogg', static: build_static)
sdl2 = dependency('SDL2')
freetype = dependency('freetype2', static: build_static)
harfbuzz = dependency('harfbuzz', static: build_static)
sdl_sound = dependency('SDL2_sound', static: build_static)
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

if host_system == 'windows'
    bz2 = dependency('bzip2')
	iconv = compilers['cpp'].find_library('iconv')
else
    bz2 = compilers['cpp'].find_library('bz2')
	iconv = compilers['cpp'].find_library('iconv')
    gtk = dependency('gtk+-2.0')
    xfconf = dependency('libxfconf-0')

	global_dependencies += [gtk, xfconf]
endif

# Windows needs to be treated like a special needs child here
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
    'audio/headers',
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

global_dependencies += [boost, bz2, openal, zlib,  sdl2, sdl_sound, pixman, physfs, vorbisfile, vorbis, iconv, ogg, sdl2_ttf, sigcxx, sdl2_image, png, jpeg, nsgif, freetype, tiff, webp, harfbuzz]

if host_system == 'windows'
    global_dependencies += compilers['cpp'].find_library('wsock32')
    global_dependencies += compilers['cpp'].find_library('winmm')
    global_dependencies += compilers['cpp'].find_library('Secur32')
    global_dependencies += compilers['cpp'].find_library('Shlwapi')
endif

main_source = files(
    'audio/source/alstream.cpp',
	'audio/source/audiostream.cpp',
	'audio/source/audiochannels.cpp',
	'audio/source/audio.cpp',
	'audio/source/soundemitter.cpp',
	'audio/source/sdlsoundsource.cpp',
	'audio/source/vorbissource.cpp',
	'filesystem/source/filesystem.cpp',
	'filesystem/source/rgssad.cpp',
	'graphics/source/autotiles.cpp',
	'graphics/source/bitmap.cpp',
	'graphics/source/font.cpp',
	'graphics/source/graphics.cpp',
	'graphics/source/plane.cpp',
	'graphics/source/rb_shader.cpp',
	'graphics/source/sprite.cpp',
	'graphics/source/scene.cpp',
	'graphics/source/tilemap.cpp',
	'graphics/source/tileatlas.cpp',
	'graphics/source/window.cpp',
	'graphics/source/viewport.cpp',
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

if host_system == 'windows'
else
    global_sources += files('oneshot/source/xdg-user-dir-lookup.c')
endif
