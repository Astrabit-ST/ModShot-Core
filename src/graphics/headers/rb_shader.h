#ifndef RB_SHADER_H
#define RB_SHADER_H

#include "glstate.h"
#include "gl-util.h"
#include "binding-util.h"
#include <map>

enum Attribute
{
	Position = 0,
	TexCoord = 1,
	Color = 2
};

class CompiledShader {
public:
    CompiledShader(const char* contents, VALUE args);
    CompiledShader(const char* contents, VALUE args, const char* vertContents);

    const char* getContents();
    const char* getVertContents();
private:
    void setupShaderSource(const char* contents, GLuint shader, bool vert);
    void compileShader(const char* contents, GLuint shader, GLuint program, bool vert);
    void setupArgs(VALUE args);

    const char* contents;
    const char* vertContents;
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