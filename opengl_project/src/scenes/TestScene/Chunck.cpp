#include <malloc.h>  
#include <iostream>
#include <vector>

#include "imgui/imgui.h"
#include "Chunck.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Chunck::Chunck()
{
	m_MyScene->m_MainCamera.SetBackgroundColor({ 34, 128, 161 });

	m_TextureTest = new TextureArray("res/textures/c.png", 16, 16, 4);

	std::vector<unsigned int> triangles;
	std::vector<Mesh::Vertex> vertices;

	bool visibleSides[]
	{
		true,
		true,
		true,
		true,
		true,
		true
	};

	uint8_t blockType[6] = { 3,0,2,2,2,2 };

	size_t vertCount = 0;
	size_t triCount = 0;

	for (size_t i = 0; i < 6; i++)
	{
		if (!visibleSides[i])
			continue;

		for (size_t j = 0; j < 4; j++)
		{
			Mesh::Vertex vertex;

			int vertexIndex = m_FaceVerticeIndexes[i][j];
			glm::uvec3 vertPosition = m_CubeVertices[vertexIndex];

			unsigned int data = 0;

			data |= vertPosition.x;
			data |= vertPosition.y << 5;
			data |= vertPosition.z << 10;

			data |= blockType[i] << 15;
			data |= j << 19;

			vertex.data = data;
			vertices.push_back(vertex);
		}

		for (size_t j = 0; j < 6; j++)
		{
			size_t vertIndex = vertCount + m_FaceTriangulation[j];
			triangles.push_back(vertIndex);
		}

		vertCount += 4;
		triCount += 6;
	}

	m_Cube.SetTriangles(&triangles[0], triCount);
	m_Cube.SetVertices(&vertices[0], vertCount);
}

void Chunck::Update()
{
	Renderer::DrawMesh(m_Cube, m_PlayerTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

Chunck::~Chunck() {}

