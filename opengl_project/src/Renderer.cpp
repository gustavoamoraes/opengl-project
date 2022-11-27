#include "Renderer.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}

struct QuadVertex
{
    glm::vec3 position = {1,2,3};
};

struct RendererData
{
    static const uint32_t MaxQuads = 2;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;

    VertexArray* QuadVertexArray;
    Shader* QuadShader;
    VertexBuffer* QuadVertexBuffer;
    VertexBufferLayout Layout;

    QuadVertex* QuadsBase = nullptr;
    QuadVertex* QuadsBasePtr = nullptr;

    glm::vec4 QuadVertexPositions[4]
    {
        { -0.5f, -0.5f, 0.0f, 1.0f},
        { 0.5f, -0.5f, 0.0f , 1.0f},
        { 0.5f,  0.5f, 0.0f, 1.0f},
        { -0.5f,  0.5f, 0.0f, 1.0f}
    };
};

static RendererData s_RenderData ;

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

void Renderer::Init()
{
    s_RenderData.QuadsBase = new QuadVertex[RendererData::MaxVertices];

    s_RenderData.QuadsBasePtr = s_RenderData.QuadsBase;

    unsigned int triangles[s_RenderData.MaxIndices];

    for (size_t i = 0; i < s_RenderData.MaxIndices; i += 6)
    {
        triangles[i] = i+0;
        triangles[i+1] = i+1;
        triangles[i+2] = i+2;

        triangles[i+3] = i+2;
        triangles[i+4] = i+3;
        triangles[i+5] = i+0;
    }

    glm::mat4 proj = glm::perspective(45.0f, 1.33f, 0.0f, 300.0f);
    
    s_RenderData.QuadShader = new Shader("res/shaders/basic_shader.shader");
    s_RenderData.QuadShader->Bind();
    s_RenderData.QuadShader->SetUniforms4f("u_Color", .5f, 0.0f, .5f, 0.0f);
    s_RenderData.QuadShader->SetUniformsMat4f("u_MVP", proj);

    s_RenderData.QuadVertexArray = new VertexArray();

    IndexBuffer* ib = new IndexBuffer(triangles, s_RenderData.MaxIndices);
    s_RenderData.QuadVertexArray->SetIndexBuffer(*ib);

    s_RenderData.Layout.Push<float>(3); //Position

    s_RenderData.QuadVertexBuffer = new VertexBuffer();
    s_RenderData.QuadVertexArray->AddBuffer(s_RenderData.Layout, *s_RenderData.QuadVertexBuffer);
}

void Renderer::Draw()
{
    int quadVertexCount = s_RenderData.QuadsBasePtr - s_RenderData.QuadsBase;
    size_t triCount = (quadVertexCount /4) * 6;

    s_RenderData.QuadVertexBuffer->SetData(s_RenderData.QuadsBase, s_RenderData.MaxVertices * sizeof(QuadVertex));

    s_RenderData.QuadShader->Bind();
    s_RenderData.QuadVertexArray->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, triCount, GL_UNSIGNED_INT, nullptr));

    //Reset
    s_RenderData.QuadsBasePtr = s_RenderData.QuadsBase;
}

void Renderer::DrawQuad(const glm::mat4 transform)
{
    for (size_t i = 0; i < 4; i++)
    {
        s_RenderData.QuadsBasePtr->position = transform * s_RenderData.QuadVertexPositions[i];
        s_RenderData.QuadsBasePtr++;
    }
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
