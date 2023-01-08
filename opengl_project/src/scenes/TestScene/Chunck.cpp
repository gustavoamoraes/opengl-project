#include <malloc.h>  
#include <iostream>
#include <vector>

#include "Chunck.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"
#include "Transform.h"
#include "ChunckManager.h"

#include "perlin_noise/PerlinNoise.hpp"

#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Chunck::Chunck(glm::vec2 chunckWorldCoord) : m_WorldChunckCoord(chunckWorldCoord)
{
	m_ChunckManager = ChunckManager::instance();
	m_TextureTest = new TextureAtlas("res/textures/c.png", 16, 16, 4, 0);
}

void Chunck::Update()
{
	Renderer::DrawMesh(m_ChunckMesh, m_ChunckTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

void Chunck::Start()
{
	//GenerateChunckVoxels();
	//UpdateChunck();
}

void Chunck::GenerateChunckVoxels()
{
	const siv::PerlinNoise::seed_type seed = 78787u;
	const siv::PerlinNoise perlin{ seed };

	size_t chunckSize = ChunckManager::m_ChunckSize;

	for (size_t x = 0; x < chunckSize; x++)
	{
		for (size_t y = 0; y < chunckSize; y++)
		{
			for (size_t z = 0; z < chunckSize; z++)
			{
				glm::vec3 globalVoxelIndex = glm::vec3(m_WorldChunckCoord.x * chunckSize + x,
					y,
					m_WorldChunckCoord.y * chunckSize + z);

				float noise = perlin.octave3D_01((globalVoxelIndex.x * 0.03), (globalVoxelIndex.y * 0.03), (globalVoxelIndex.z * 0.03), 4);
				m_Blocks[x][y][z] = (noise > 0.6f) ? 4 : 0;
			}
		}
	}
}

void Chunck::AddVoxelFaces(glm::vec3 localVoxelIndex)
{
	int chunckSize = ChunckManager::m_ChunckSize;

	glm::vec3 globalVoxelIndex = glm::vec3(m_WorldChunckCoord.x * chunckSize + localVoxelIndex.x,
		localVoxelIndex.y,
		m_WorldChunckCoord.y * chunckSize + localVoxelIndex.z);

	ChunckManager::Block currentBlock = GetBlock(localVoxelIndex);

	//Return if its air
	if (!currentBlock)
		return;

	bool visibleSides[]
	{
		!m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::up), //Up
		!m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::up), //Bottom
		!m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::forward), //Front
		!m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::forward), //Back
		!m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::right), //Right
		!m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::right), //Left
	};

	for (size_t i = 0; i < 6; i++)
	{
		if (!visibleSides[i])
			continue;

		for (size_t j = 0; j < 6; j++)
		{
			size_t vertIndex = m_VerticeCount + m_FaceTriangulation[j];
			m_Triangles[m_TriangleCount+j] = vertIndex;
		}

		for (size_t j = 0; j < 4; j++)
		{
			Mesh::Vertex vertex;

			int vertexIndex = m_FaceVerticeIndexes[i][j];
			glm::uvec3 vertPosition = localVoxelIndex + m_CubeVertices[vertexIndex];

			unsigned int vertexData = 0;

			vertexData |= vertPosition.x;
			vertexData |= vertPosition.y << 5;
			vertexData |= vertPosition.z << 10;
			vertexData |= currentBlock << 15;
			vertexData |= j << 19;

			vertex.data = vertexData;
			m_Vertices[m_VerticeCount + j] = vertex;
		}

		m_VerticeCount += 4;
		m_TriangleCount += 6;
	}
}

void Chunck::CreateChunckMesh()
{
	m_Triangles = (unsigned int*)malloc(ChunckManager::m_MaxVoxelsPerChunck * 6 * 6 * sizeof(unsigned int));
	m_Vertices = (Mesh::Vertex*) malloc(ChunckManager::m_MaxVoxelsPerChunck * 4 * 6 * sizeof(Mesh::Vertex));

	size_t chunckSize = ChunckManager::m_ChunckSize;

	for (size_t x = 0; x < chunckSize; x++)
	{
		for (size_t y = 0; y < chunckSize; y++)
		{
			for (size_t z = 0; z < chunckSize; z++)
			{
				AddVoxelFaces(glm::vec3(x,y,z));
			}
		}
	}

	m_ChunckMesh.SetTriangles(m_Triangles, m_TriangleCount);
	m_ChunckMesh.SetVertices(m_Vertices, m_VerticeCount);

	free(m_Triangles);
	free(m_Vertices);
}

void Chunck::UpdateChunck() 
{
	m_ChunckTransform.m_Position = glm::vec3(m_WorldChunckCoord.x * ChunckManager::m_ChunckSize, 0, m_WorldChunckCoord.y * ChunckManager::m_ChunckSize);

	CreateChunckMesh();
}

ChunckManager::Block Chunck::GetBlock(glm::uvec3 localIndex)
{
	return m_Blocks[localIndex.x][localIndex.y][localIndex.z];
}

Chunck::~Chunck() {}

