#include "binding-util.h"
#include "rb_shader.h"
#include "shadable-element-binding.h"

DEF_TYPE_CUSTOMNAME(CustomShader, "Shader");

RB_METHOD(shaderInitialize)
{
    VALUE compiledShaderObj;
    VALUE hashArgs = 0;

    rb_get_args(argc, argv, "o|o", &compiledShaderObj, &hashArgs);

    CompiledShader *compiledShader = getPrivateData<CompiledShader>(compiledShaderObj);

    rb_iv_set(self, "compiled_shader", compiledShaderObj);

    if (!hashArgs)
        hashArgs = rb_hash_new();

    rb_iv_set(self, "args", hashArgs);

    CustomShader *shader = new CustomShader(compiledShader, hashArgs);

    setPrivateData(self, shader);

    return self;
}

RB_METHOD(shaderCompile)
{
    VALUE contents;
    VALUE aryArgs;
    VALUE vertContents = 0;

    rb_get_args(argc, argv, "oo|o", &contents, &aryArgs RB_ARG_END);

    VALUE passedArgs[] = {contents, aryArgs, vertContents};

    VALUE classConst = rb_const_get(rb_cObject, rb_intern("CompiledShader"));
    VALUE shaderObj = rb_class_new_instance(3, passedArgs, classConst);

    return shaderObj;
}

RB_METHOD(shaderArgs)
{
    RB_UNUSED_PARAM;

    return rb_iv_get(self, "args");
}

RB_METHOD(shaderGetCompiledShader)
{
    RB_UNUSED_PARAM;

    return rb_iv_get(self, "compiled_shader");
}

RB_METHOD(shaderStringify)
{
    RB_UNUSED_PARAM;

    CustomShader *shader = getPrivateData<CustomShader>(self);

    return rb_sprintf(
        "<#Shader:%p private_shader=%p args=%" PRIsVALUE " compiled_shader=%" PRIsVALUE ">",
        (void *)self,
        (void *)shader,
        rb_iv_get(self, "args"),
        rb_iv_get(self, "compiled_shader"));
}

void shaderBindingInit()
{
    VALUE klass = rb_define_class("Shader", rb_cObject);
    rb_define_alloc_func(klass, classAllocate<&CustomShaderType>);

    _rb_define_method(klass, "initialize", shaderInitialize);
    _rb_define_module_function(klass, "compile", shaderCompile);
    _rb_define_method(klass, "args", shaderArgs);
    _rb_define_method(klass, "compiled_shader", shaderGetCompiledShader);
    _rb_define_method(klass, "to_s", shaderStringify);
    _rb_define_method(klass, "inspect", shaderStringify);
}