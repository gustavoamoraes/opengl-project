#pragma once

#include <GL/glew.h>

#include "Buffer.h"
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
		static void Draw(const Shader& shader, const VertexArray& vertexArray, size_t trianglesCount);
		static void Clear();
};