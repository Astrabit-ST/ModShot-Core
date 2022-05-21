#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE(CompiledShader);

RB_METHOD(comiledShaderInitialize) {
    const char* contents;
    VALUE typeSym;
    VALUE aryArgs;

    rb_get_args(argc, argv, "zoo", &contents, &typeSym, &aryArgs);

    CompiledShader *shader = new CompiledShader(contents, typeSym == rb_intern("vert"), aryArgs);
    setPrivateData(self, shader);

    rb_ary_freeze(aryArgs);

    rb_iv_set(self, "args", aryArgs);

    return self;
}

RB_METHOD(compiledShaderArgs) {
    RB_UNUSED_PARAM;

    return rb_iv_get(self, "args");
}

void compiledShaderBindingInit() {
    compiledShaderClass = rb_define_class_under(shaderClass, "CompiledShader", rb_cObject);

    _rb_define_method(compiledShaderClass, "args", compiledShaderArgs);
}