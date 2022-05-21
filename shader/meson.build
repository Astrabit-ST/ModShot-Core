embedded_shaders = [
    'bitmapBlit.frag',
    'blur.frag',
    'blurH.vert',
    'blurV.vert',
    'common.h',
    'flashMap.frag',
    'flatColor.frag',
    'gray.frag',
    'hue.frag',
    'minimal.vert',
    'obscured.frag',
    'plane.frag',
    'simple.frag',
    'simple.vert',
    'simpleAlpha.frag',
    'simpleAlphaUni.frag',
    'simpleColor.frag',
    'simpleColor.vert',
    'simpleMatrix.vert',
    'sprite.frag',
    'sprite.vert',
    'tilemap.vert',
    'trans.frag',
    'transSimple.frag',
    'rb_simple.vert'
]

embedded_shaders_f = files(embedded_shaders)

count = 0
foreach file : embedded_shaders_f
    global_sources += custom_target(embedded_shaders[count],
        input: file,
        output: '@0@.xxd'.format(embedded_shaders[count]),
        command: [
            xxd, '-i', '@INPUT@'
        ],
        capture: true,
        depend_files: embedded_shaders_f[count]
        )
    count += 1
endforeach
