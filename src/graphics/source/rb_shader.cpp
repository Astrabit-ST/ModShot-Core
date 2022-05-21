#include "rb_shader.h"
#include "binding-util.h"

void compileShader() {

}

CompiledShader::CompiledShader(const char* contents, bool vert, VALUE args) {

}

CustomShader::CustomShader(CompiledShader shader, VALUE* args):
    shader(shader),
    args(args)
{

}