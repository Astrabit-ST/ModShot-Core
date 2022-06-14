win = import('windows')

res = files(
    'resource.h',
    'icon.ico',
    'manifest.xml'
)

windows_resources = win.compile_resources('resource.rc', depend_files: res)

meson.add_install_script('sh', '../windows/install.sh', meson.project_name() + '.exe', meson.project_name() + '-shim.exe', get_option('mri_version'))
