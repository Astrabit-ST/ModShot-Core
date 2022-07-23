if get_option('mri_includes') == ''
    ver = get_option('mri_version')
    if ver.version_compare('>=3.0') and compilers['cpp'].get_id() == 'clang'
        global_args += '-fdeclspec'
    endif
    global_dependencies += dependency('ruby-' + ver)
else
    global_args += ('-I' + get_option('mri_includes'))
    global_dependencies += compilers['cpp'].find_library(get_option('mri_library'), dirs: get_option('mri_libpath'))
endif

global_include_dirs += include_directories('.')

binding_source = [files(
    'aleffect-binding.cpp',
    'audio-binding.cpp',
    'compiled-shader-binding.cpp',
    'binding-mri.cpp',
    'binding-util.cpp',
    'bitmap-binding.cpp',
    'etc-binding.cpp',
    'etc-internal-binding.cpp',
    'filesystem-binding.cpp',
    'font-binding.cpp',
    'graphics-binding.cpp',
    'input-binding.cpp',
    'journal-binding.cpp',
    'module_rpg.cpp',
    'niko-binding.cpp',
    'oneshot-binding.cpp',
    'modshot-binding.cpp',
    'plane-binding.cpp',
    'screen-binding.cpp',
    'shader-binding.cpp',
    'sprite-binding.cpp',
    'steam-binding.cpp',
    'table-binding.cpp',
    'tilemap-binding.cpp',
    'viewport-binding.cpp',
    'wallpaper-binding.cpp',
    'window-binding.cpp',
)]

if fmod
global_sources += [files(
    'fmod-binding/studio/fmod-studio-binding.cpp',
    'fmod-binding/studio/system.cpp',
    'fmod-binding/studio/bank.cpp',
    'fmod-binding/studio/vca.cpp',
    'fmod-binding/studio/bus.cpp',
    'fmod-binding/studio/eventdescription.cpp',
    'fmod-binding/studio/eventinstance.cpp',
    'fmod-binding/studio/commandreplay.cpp',
    'fmod-binding/studio/common_structs.cpp',
    'fmod-binding/core/fmod-core-binding.cpp',
    'fmod-binding/core/system.cpp',
    'fmod-binding/core/common_structs.cpp',
    'fmod-binding/fmod_enums.cpp',
)]
global_include_dirs += include_directories('fmod-binding')
else
global_sources += [files(
    'al-binding/aleffect-binding.cpp',
    'al-binding/audio-binding.cpp'
)]
endif

global_sources += binding_source
