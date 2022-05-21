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
    const char* contents;
    VALUE typeSym;
    VALUE varArr;

    rb_get_args(argc, argv, "zoo", &contents, &typeSym, &varArr);

    CompiledShader *shader = new CompiledShader(contents, typeSym == rb_intern("vert"), varArr);
    VALUE shaderObj = rb_class_new_instance(0, new VALUE[0], compiledShaderClass);
    setPrivateData(shaderObj, shader);

    return shaderObj;
}

void shaderBindingInit() {
    shaderClass = rb_define_class("Shader", rb_cObject);

    _rb_define_method(shaderClass, "initialize", shaderInitialize);
    _rb_define_module_function(shaderClass, "compile", shaderCompile);
}