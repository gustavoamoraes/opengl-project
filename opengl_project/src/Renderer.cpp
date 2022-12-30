#include "Renderer.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.h"

void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}

Mesh::Mesh() : m_TriangleCount(0), m_VerticeCount(0)
{
    m_Shader = new Shader("res/shaders/basic_shader.shader");

    m_VertexArray = new VertexArray();
    m_IndexBuffer = new IndexBuffer();
    m_VertexBuffer = new VertexBuffer();

    m_Layout.Push<unsigned int>(1);
    //m_Layout.Push<int>(1);

    m_VertexArray->AddBuffer(m_Layout, *m_VertexBuffer);
}

void Mesh::SetTriangles (const unsigned int* triangles, unsigned int count)
{
    m_IndexBuffer->SetData(triangles, count);
    m_VertexArray->SetIndexBuffer(*m_IndexBuffer);
    m_TriangleCount = count;
}

void Mesh::SetVertices(Vertex* vertices, unsigned int count)
{
    m_VertexBuffer->SetData(vertices, count * sizeof(Vertex));
    m_VerticeCount = count;
}

void Mesh::Select()
{
    m_VertexArray->Bind();
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

void Renderer::DrawMesh(Mesh& mesh, const glm::mat4 meshTransform, const glm::mat4 viewProjection)
{
    mesh.m_Shader->Bind();
    mesh.m_Shader->SetUniformsMat4f("u_Transform", meshTransform);
    mesh.m_Shader->SetUniformsMat4f("u_ViewProjection", viewProjection);
    mesh.m_Shader->SetUniforms1i("u_Texture", 0);

    mesh.Select();

    GLCall(glDrawElements(GL_TRIANGLES, mesh.m_TriangleCount, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Init()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}
