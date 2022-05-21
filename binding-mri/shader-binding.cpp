#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE_CUSTOMNAME(CustomShader, "Shader");

RB_METHOD(shaderInitialize) {
    VALUE compiledShaderObj;
    VALUE hashArgs = 0;
    
    rb_get_args(argc, argv, "o|o", &compiledShaderObj, &hashArgs);

    CompiledShader *compiledShader = getPrivateData<CompiledShader>(compiledShaderObj);

    if (!hashArgs)
        hashArgs = rb_hash_new();

    rb_iv_set(self, "args", hashArgs);

    CustomShader *shader = new CustomShader(*compiledShader, &hashArgs);

    setPrivateData(self, shader);

    return self;
}

RB_METHOD(shaderCompile) {
    VALUE contents;
    VALUE typeSym;
    VALUE aryArgs;

    rb_get_args(argc, argv, "ooo", &contents, &typeSym, &aryArgs RB_ARG_END);

    VALUE passedArgs[] = {contents, typeSym, aryArgs};

    VALUE classConst = rb_const_get(rb_cObject, rb_intern("CompiledShader"));
    VALUE shaderObj = rb_class_new_instance(3, passedArgs, classConst);

    return shaderObj;
}

RB_METHOD(shaderArgs) {
    RB_UNUSED_PARAM;

    return rb_iv_get(self, "args");
}

void shaderBindingInit() {
    VALUE klass = rb_define_class("Shader", rb_cObject);
    rb_define_alloc_func(klass, classAllocate<&CustomShaderType>);

    _rb_define_method(klass, "initialize", shaderInitialize);
    _rb_define_module_function(klass, "compile", shaderCompile);
    _rb_define_method(klass, "args", shaderArgs);
}