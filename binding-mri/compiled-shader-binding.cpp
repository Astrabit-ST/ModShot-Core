#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE(CompiledShader);

RB_METHOD(comiledShaderInitialize) {
    const char* contents;
    VALUE aryArgs;
    VALUE vertContents = 0;

    rb_get_args(argc, argv, "zo|o", &contents, &aryArgs, &vertContents RB_ARG_END);

    CompiledShader *shader;
    if (vertContents) {
        shader = new CompiledShader(contents, aryArgs, rb_string_value_cstr(&vertContents));
    } else {
        shader = new CompiledShader(contents, aryArgs);
    }
    setPrivateData(self, shader);

    rb_ary_freeze(aryArgs);

    rb_iv_set(self, "args", aryArgs);

    return self;
}

RB_METHOD(compiledShaderArgs) {
    RB_UNUSED_PARAM;

    return rb_iv_get(self, "args");
}

RB_METHOD(compiledShaderGetContents) {
    RB_UNUSED_PARAM;

    CompiledShader *shader = getPrivateData<CompiledShader>(self);

    return rb_str_new_cstr(shader->getContents());
}

RB_METHOD(compiledShaderGetVertContents) {
    RB_UNUSED_PARAM;

    CompiledShader *shader = getPrivateData<CompiledShader>(self);

    return rb_str_new_cstr(shader->getVertContents());
}

void compiledShaderBindingInit() {
    VALUE klass = rb_define_class("CompiledShader", rb_cObject);
    rb_define_alloc_func(klass, classAllocate<&CompiledShaderType>);

    _rb_define_method(klass, "initialize", comiledShaderInitialize);
    _rb_define_method(klass, "args", compiledShaderArgs);
    _rb_define_method(klass, "contents", compiledShaderGetContents);
    _rb_define_method(klass, "vert_contents", compiledShaderGetVertContents);
}