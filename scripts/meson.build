global_sources += custom_target('pack scripts',
    output: 'xScripts.rxdata',
    command: [
            ruby,
            meson.current_source_dir() + '/ruby/rpgscript.rb',
            '-s', meson.current_source_dir() + '/rgss',
            '-o', '@OUTPUT@'
        ],
    install: true,
    install_dir: 'Data',
    build_always_stale: true
)
