#pragma once

#include <vector>
#include "GL/glew.h"
//#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int size;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:

	VertexBufferLayout() : m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		//ASSERT(false);
	}

	template<>
	void Push <float>(unsigned int count)
	{
		unsigned int size = count * sizeof(float);
		m_Elements.push_back({ GL_FLOAT, count, size });
		m_Stride += size;
	}

	template<>
	void Push <unsigned int>(unsigned int count)
	{
		unsigned int size = count * sizeof(unsigned int);
		m_Elements.push_back({ GL_INT, count, size });
		m_Stride += size;
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline const unsigned int GetStride() const { return m_Stride; }
};

class VertexBuffer
{
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer();
		~VertexBuffer();

		void SetData(const void* data, unsigned int size);
		void Bind() const;
		void Unbind() const;
};

class IndexBuffer
{
	private:
		unsigned int m_RendererID;
	public:
		IndexBuffer();
		~IndexBuffer();

		void SetData(const unsigned int* data, unsigned int count);
		void Bind() const;
		void Unbind() const;

		unsigned int m_IndexCount;
};