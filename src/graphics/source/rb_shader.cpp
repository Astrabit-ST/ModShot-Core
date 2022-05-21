#include "rb_shader.h"
#include "glstate.h"
#include "gl-util.h"
#include "binding-util.h"

#include "rb_simple.vert.xxd"

#include <string>

CompiledShader::CompiledShader(const char* contents, VALUE args):
    contents(contents)
{
    fragShader = gl.CreateShader(GL_FRAGMENT_SHADER);
    vertShader = gl.CreateShader(GL_VERTEX_SHADER);

    program = gl.CreateProgram();
    
    compileShader(contents, fragShader, program, false);
    compileShader((const char*) ___shader_rb_simple_vert, vertShader, program, true);
}

CustomShader::CustomShader(CompiledShader shader, VALUE* args):
    shader(shader),
    args(args)
{

}

std::string getShaderLog(GLuint shader)
{
	GLint logLength;
	gl.GetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

	std::string log(logLength, '\0');
	gl.GetShaderInfoLog(shader, log.size(), 0, &log[0]);

	return log;
}


void CompiledShader::setupShaderSource(const char* contents, GLuint shader, bool vert) {
    static const char glesDefine[] = "#define GLSLES\n";
	static const char fragDefine[] = "#define FRAGMENT_SHADER\n";

	const GLchar *shaderSrc[3];
	GLint shaderSrcSize[3];
	size_t i = 0;

    if (gl.glsles)
	{
		shaderSrc[i] = glesDefine;
		shaderSrcSize[i] = sizeof(glesDefine)-1;
		++i;
	}

    if (!vert)
	{
		shaderSrc[i] = fragDefine;
		shaderSrcSize[i] = sizeof(fragDefine)-1;
		++i;
	}

    shaderSrc[i] = (const GLchar*) contents;
	shaderSrcSize[i] = strlen(contents);
	++i;

    gl.ShaderSource(shader, i, shaderSrc, shaderSrcSize);
}

void CompiledShader::compileShader(const char* contents, GLuint shader, GLuint program, bool vert) {
    GLint success;

    setupShaderSource(contents, shader, vert);
    gl.CompileShader(shader);

    gl.GetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        rb_raise(rb_eRuntimeError, "Shader compilation failed with: %s", getShaderLog(shader).c_str());
        return;
    }

    gl.AttachShader(program, shader);
    
    gl.BindAttribLocation(program, Position, "position");
	gl.BindAttribLocation(program, TexCoord, "texCoord");
	gl.BindAttribLocation(program, Color, "color");

    gl.LinkProgram(program);

	gl.GetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        rb_raise(rb_eRuntimeError, "Shader linking failed with: %s", getShaderLog(program).c_str());
        return;
    }
}