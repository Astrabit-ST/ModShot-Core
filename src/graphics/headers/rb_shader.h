#ifndef RB_SHADER_H
#define RB_SHADER_H

#include "glstate.h"
#include "gl-util.h"
#include "binding-util.h"
#include <map>

class CompiledShader {
public:
    CompiledShader(const char* contents, bool vert, VALUE args);
private:
    std::map<const char*, GLint> args;
    GLuint vertShader;
    GLuint fragShader;
    GLuint program;
};
class CustomShader {
public: 
    CustomShader(CompiledShader shader, VALUE* args);
private:
    CompiledShader shader;
    VALUE* args;
};

#endif