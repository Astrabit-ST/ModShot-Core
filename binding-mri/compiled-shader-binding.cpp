#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE(CompiledShader);

RB_METHOD(compiledShaderArgs) {
    RB_UNUSED_PARAM;

    return rb_iv_get(self, "args");
}

void compiledShaderBindingInit() {
    compiledShaderClass = rb_define_class_under(shaderClass, "CompiledShader", rb_cObject);

    _rb_define_method(compiledShaderClass, "args", compiledShaderArgs);
}