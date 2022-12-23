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

class Mesh
{
public:

    struct Vertex
    {
        glm::vec3 position = { 0,0,0 };
        glm::vec2 texCoord = { 0,0};
    };

    Shader* m_Shader;
    uint32_t m_TriangleCount;
    uint32_t m_VerticeCount;

    Mesh();

    void SetTriangles(const unsigned int* triangles, unsigned int count);
    void SetVertices(Vertex* vertices, unsigned int count);

    void Select();

private:
    VertexArray* m_VertexArray;
    VertexBuffer* m_VertexBuffer;
    IndexBuffer* m_IndexBuffer;
    VertexBufferLayout m_Layout;
};

class Renderer
{
	public:
		//static void Init();
        static void DrawMesh(Mesh& mesh, const glm::mat4 meshTransform, const glm::mat4 viewProjection);
		static void Clear();
};
