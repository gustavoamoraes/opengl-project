#pragma once

#include "Buffer.h"
#include <memory>

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBufferLayout& layout, const VertexBuffer& vb);
	void SetIndexBuffer(const IndexBuffer& indexBuffer);

	std::shared_ptr<IndexBuffer>  GetIndexBuffer() { return std::shared_ptr<IndexBuffer>(m_IndexBuffer);}

	void Bind() const;
	void Unbind() const;

private:
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	//std::unique_ptr<VertexBuffer> m_VertexBuffer;
};
