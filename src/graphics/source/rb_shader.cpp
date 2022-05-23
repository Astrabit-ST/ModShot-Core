#include "rb_shader.h"
#include "glstate.h"
#include "gl-util.h"
#include "binding-util.h"
#include "sharedstate.h"
#include "shader.h"
#include "rb_simple.vert.xxd"

#include <string>
#include <map>

CompiledShader::CompiledShader(const char *contents, VALUE args) : contents(contents),
                                                                   vertContents((const char *)___shader_rb_simple_vert)
{
    fragShader = gl.CreateShader(GL_FRAGMENT_SHADER);
    vertShader = gl.CreateShader(GL_VERTEX_SHADER);

    program = gl.CreateProgram();

    compileShader(contents, fragShader, program, false);
    compileShader(vertContents, vertShader, program, true);
    setupArgs(args);

    ShaderBase::init();
}

CompiledShader::CompiledShader(const char *contents, VALUE args, const char *vertContents) : contents(contents),
                                                                                             vertContents(vertContents)
{
    fragShader = gl.CreateShader(GL_FRAGMENT_SHADER);
    vertShader = gl.CreateShader(GL_VERTEX_SHADER);

    program = gl.CreateProgram();

    compileShader(contents, fragShader, program, false);
    compileShader(vertContents, vertShader, program, true);
    setupArgs(args);

    ShaderBase::init();
}

std::string getShaderLog(GLuint shader)
{
    GLint logLength;
    gl.GetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    std::string log(logLength, '\0');
    gl.GetShaderInfoLog(shader, log.size(), 0, &log[0]);

    return log;
}

void CompiledShader::setupShaderSource(const char *contents, GLuint shader, bool vert)
{
    static const char glesDefine[] = "#define GLSLES\n";
    static const char fragDefine[] = "#define FRAGMENT_SHADER\n";

    const GLchar *shaderSrc[3];
    GLint shaderSrcSize[3];
    size_t i = 0;

    if (gl.glsles)
    {
        shaderSrc[i] = glesDefine;
        shaderSrcSize[i] = sizeof(glesDefine) - 1;
        ++i;
    }

    if (!vert)
    {
        shaderSrc[i] = fragDefine;
        shaderSrcSize[i] = sizeof(fragDefine) - 1;
        ++i;
    }

    shaderSrc[i] = (const GLchar *)contents;
    shaderSrcSize[i] = strlen(contents);
    ++i;

    gl.ShaderSource(shader, i, shaderSrc, shaderSrcSize);
}

void CompiledShader::compileShader(const char *contents, GLuint shader, GLuint program, bool vert)
{
    GLint success;

    setupShaderSource(contents, shader, vert);
    gl.CompileShader(shader);

    gl.GetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        rb_raise(rb_eRuntimeError, "Shader compilation failed with: \n%s", getShaderLog(shader).c_str());
        return;
    }

    gl.AttachShader(program, shader);

    gl.BindAttribLocation(program, Position, "position");
    gl.BindAttribLocation(program, TexCoord, "texCoord");
    gl.BindAttribLocation(program, Color, "color");

    gl.LinkProgram(program);

    gl.GetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        rb_raise(rb_eRuntimeError, "Shader linking failed with: \n%s", getShaderLog(program).c_str());
        return;
    }
}

void CompiledShader::setupArgs(VALUE pargs)
{
    long argc = rb_array_len(pargs);
    args = std::map<const char *, GLint>();

    for (long i = 0; i < argc; ++i)
    {
        VALUE arg = rb_ary_entry(pargs, i);
        const char *name = rb_string_value_cstr(&arg);
        args[name] = gl.GetUniformLocation(program, name);
    }
}

const char *CompiledShader::getContents()
{
    return contents;
}

const char *CompiledShader::getVertContents()
{
    return vertContents;
}

std::map<const char *, GLint> CompiledShader::getArgs()
{
    return args;
}

GLuint CompiledShader::getProgram()
{
    return program;
}

CustomShader::CustomShader(CompiledShader* shader, VALUE args) : shader(shader),
                                                                args(args)
{
}

GLint CustomShader::getUniform(const char *name)
{
    return gl.GetUniformLocation(shader->getProgram(), name);
}

bool CustomShader::supportsSpriteMat()
{
    GLint u = getUniform("spriteMat");
    return getUniform("spriteMat") != -1;
}

void CustomShader::setSpriteMat(const float value[16])
{
    gl.UniformMatrix4fv(getUniform("spriteMat"), 1, GL_FALSE, value);
}

void CustomShader::applyArgs()
{
    std::map<const char *, GLint> args = shader->getArgs();
    std::map<const char *, GLint>::iterator it;
    for (it = args.begin(); it != args.end(); it++)
    {
        VALUE value = rb_hash_aref(this->args, rb_str_new_cstr(it->first));

        if (value == Qnil)
        {
            rb_raise(rb_eIndexError, "No such argument: %s", it->first);
        }

        const char *class_name = rb_obj_classname(value);
        if (class_name)
        {
        }
        else
        {
            rb_raise(rb_eArgError, "Argument %s is of type %s, which is not a supported type", it->first, class_name);
            break;
        }
    }
}

CompiledShader* CustomShader::getShader()
{
    return shader;
}