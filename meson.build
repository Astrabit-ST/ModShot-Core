# ModShot Meson project build file
project(
    'modshot',
    ['c', 'cpp'],
    version: '1.0.0',
    license: 'GPL-2.0',
    meson_version: '>=0.56.0',
    default_options: [
        'cpp_std=c++14',
        'buildtype=release'
    ]
)

host_system = host_machine.system()

compilers = {
    'cpp': meson.get_compiler('cpp')
}

xxd = find_program('xxd', native: true)

global_sources = []
global_dependencies = []
global_include_dirs = []
global_args = []
global_link_args = []

sizeof = {
    'void*': compilers['cpp'].sizeof('void*'),
    'long': compilers['cpp'].sizeof('long')
}
win64 = (sizeof['void*'] != sizeof['long'])

global_args += '-DHAVE_NANOSLEEP'

gfx_backend = get_option('gfx_backend')
if gfx_backend == 'gles'
    global_args += '-DGLES2_HEADER'
elif gfx_backend == 'gl'
    global_dependencies += dependency('gl')
endif

# ====================
# Main source
# ====================

# Suppress warnings
global_args += [
    '-Wno-non-virtual-dtor',
    '-Wno-reorder',
    '-Wno-uninitialized',
    '-Wno-unknown-pragmas',
    '-Wno-stringop-truncation',
    '-Wno-parentheses',
    '-Wno-sign-compare',
    '-Wno-misleading-indentation'
]

if compilers['cpp'].get_id() == 'clang'
    global_args += [
        '-Wno-undefined-var-template',
        '-Wno-delete-non-abstract-non-virtual-dtor'
    ]
endif

if host_system == 'windows'
    # Win32 Subsystem and Operating System version
    # (default: 6.00 - Windows Vista/7 and higher)
    winnt_ver_args = [
        '-Wl,--major-subsystem-version=6',
        '-Wl,--minor-subsystem-version=0',
        '-Wl,--major-os-version=6',
        '-Wl,--minor-os-version=0'
    ]
    global_link_args += winnt_ver_args

    if compilers['cpp'].get_id() != 'clang'
        global_args += '-masm=intel'
    endif
endif

# Defines
if get_option('workdir_current')
    global_args += '-DWORKDIR_CURRENT'
endif

steam = false
if get_option('steam') == true
    steam = true
endif

build_static = false
if get_option('build_static') == true 
    if host_system == 'windows'
        build_static = true
    endif
endif

# Project subdirectories
subdir('src')
subdir('binding-mri')
subdir('shader')
subdir('assets')

global_include_dirs += include_directories('src', 'binding-mri')

rpath = ''
if host_system == 'windows'
    subdir('windows')
    global_sources += windows_resources
    global_include_dirs += include_directories('windows')
else
    subdir('linux')
    rpath = '$ORIGIN'
endif

exe_name = meson.project_name()

# ModShot Build
executable(
    exe_name,
    sources: global_sources,
    dependencies: global_dependencies,
    include_directories: global_include_dirs,
    install_rpath: rpath,
    link_args: global_link_args,
    cpp_args: global_args,
    objc_args: global_args,
    objcpp_args: global_args,
    win_subsystem: 'windows',
    install: (host_system != 'windows')
)

# ModShot Shim for Windows
if host_system == 'windows'
    executable(
        meson.project_name() + '-shim',
        sources: [
            'windows/shim.c',
            windows_resources
        ],
        link_args: [
            winnt_ver_args
        ],
        win_subsystem: 'windows'
    )
endif
