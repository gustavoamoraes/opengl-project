#pragma once

#include <vector>
#include <gl/glew.h>
#include <iostream>
#include "Renderer.h"

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
		void Push (unsigned int count)
		{
			ASSERT(false);
		}

		template<>
		void Push <float> (unsigned int count)
		{	
			unsigned int size = count * sizeof(float);
			m_Elements.push_back({ GL_FLOAT, count, size });
			m_Stride += size;
		}

		inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
		inline const unsigned int GetStride() const { return m_Stride; }
};