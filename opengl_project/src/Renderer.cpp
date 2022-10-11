#include "Renderer.h"
#include <iostream>

void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, int line, const char* file)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") "
            << function << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

void Renderer::Draw(const Shader& shader, const VertexArray& va, size_t trianglesCount)
{
    shader.Bind();
    va.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
