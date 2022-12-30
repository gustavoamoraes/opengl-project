#include <gl/glew.h>
#include "Renderer.h"

#include "Buffer.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::SetIndexBuffer(const IndexBuffer& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer.Bind();
    m_IndexBuffer = std::make_shared<IndexBuffer>(indexBuffer);
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout, const VertexBuffer& vb)
{
    vb.Bind();

    unsigned int offset = 0;
    const auto& elements = layout.GetElements();

    for (size_t i = 0; i < elements.size(); i++)
    {
        GLCall(glEnableVertexAttribArray(i));

        if (elements[i].type == GL_INT)
        {
            GLCall(glVertexAttribIPointer(i, elements[i].count, elements[i].type,
                layout.GetStride(), (const void*)offset));
        }
        else 
        {
            GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, GL_FALSE,
                layout.GetStride(), (const void*)offset));
        }

        offset += elements[i].size;
    }
}
