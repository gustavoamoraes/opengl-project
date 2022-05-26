#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>

Shader::Shader(const std::string& filepath) : m_RendererID(0), m_FilePath(filepath)
{
    ShaderProgramSource shaderSource = ParseShader(m_FilePath);
    GLCall(m_RendererID = glCreateProgram());

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, shaderSource.vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shaderSource.fragmentShader);

    GLCall(glAttachShader(m_RendererID, vs));
    GLCall(glAttachShader(m_RendererID, fs));

    GLCall(glLinkProgram(m_RendererID));
    GLCall(glValidateProgram(m_RendererID));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    GLCall(glUseProgram(m_RendererID));
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const
{
    GLCall(unsigned int shaderId = glCreateShader(type));
    const char* str = source.c_str();
    GLCall(glShaderSource(shaderId, 1, &str, nullptr));
    GLCall(glCompileShader(shaderId));

    int result;

    GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int lenght;
        GLCall(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &lenght));
        char* msg = (char*)alloca(lenght * sizeof(char));
        GLCall(glGetShaderInfoLog(shaderId, lenght, &lenght, msg));

        std::cout << "Failed to compite " << (type == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader") << std::endl;
        std::cout << msg << std::endl;
    }

    return shaderId;
}

ShaderProgramSource Shader::ParseShader(const std::string& dir) const
{
    std::ifstream stream(dir);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType currentType;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                currentType = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                currentType = ShaderType::FRAGMENT;

            continue;
        }

        ss[(int)currentType] << line << std::endl;
    }

    return { ss[0].str(), ss[1].str() };
}

void Shader::SetUniforms4f(const std::string& name, float v0, float v1, float v2, float v3)
{   
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformsMat4f(const std::string& name, const glm::mat4& mat)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void Shader::SetUniforms1i(const std::string& name, int i0)
{
    GLCall(glUniform1i(GetUniformLocation(name), i0));
}

int Shader::GetUniformLocation(const std::string& name)
{   
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    m_UniformLocationCache[name] = location;

    if (location == -1)
        std::cout << "Uniform \"" << name << "\" does not exist.";

    return location;
}