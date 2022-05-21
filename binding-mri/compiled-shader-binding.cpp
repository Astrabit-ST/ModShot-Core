#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE(CompiledShader);

RB_METHOD(comiledShaderInitialize) {
    const char* contents;
    VALUE aryArgs;

    rb_get_args(argc, argv, "zo", &contents, &aryArgs RB_ARG_END);

    CompiledShader *shader = new CompiledShader(contents, aryArgs);
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
    VALUE klass = rb_define_class("CompiledShader", rb_cObject);
    rb_define_alloc_func(klass, classAllocate<&CompiledShaderType>);

    _rb_define_method(klass, "initialize", comiledShaderInitialize);
    _rb_define_method(klass, "args", compiledShaderArgs);
}