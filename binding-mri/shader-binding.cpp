#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE_CUSTOMNAME(CustomShader, "Shader");

RB_METHOD(shaderInitialize) {
    VALUE compiledShaderObj;
    VALUE hashArgs;
    
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
    VALUE passedArgs [3];

    rb_get_args(argc, argv, "ooo", &passedArgs[0], &passedArgs[1], &passedArgs[2]);

    VALUE shaderObj = rb_class_new_instance(3, passedArgs, compiledShaderClass);

    return shaderObj;
}

void shaderBindingInit() {
    shaderClass = rb_define_class("Shader", rb_cObject);

    _rb_define_method(shaderClass, "initialize", shaderInitialize);
    _rb_define_module_function(shaderClass, "compile", shaderCompile);
}