#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void GLClearErrors();
bool GLLogCall(const char* function, int line, const char* file);

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
    x;\
    ASSERT(GLLogCall(#x, __LINE__, __FILE__));

class Renderer
{
	public:
		void Draw(const IndexBuffer& ib, const VertexArray& va, const Shader& shader) const;
		void Clear();
};