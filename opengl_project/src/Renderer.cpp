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

void Renderer::Draw(const IndexBuffer& ib, const VertexArray& va, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
