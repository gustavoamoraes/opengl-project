#include <malloc.h>  
#include <iostream>
#include <vector>

#include "Chunck.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"
#include "Transform.h"
#include "ChunckManager.h"

#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Chunck::Chunck(glm::vec3 chunckWorldCoord) : m_WorldChunckCoord(chunckWorldCoord)
{
}

void Chunck::Update()
{
	Renderer::DrawMesh(m_ChunckMesh, m_ChunckTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

void Chunck::Start()
{
	m_TextureTest = new TextureAtlas("res/textures/c.png", 16, 16, 4, 0);
	m_ChunckManager = ChunckManager::instance();

	GenerateChunckVoxels();
	UpdateChunck();
}

void Chunck::GenerateChunckVoxels()
{
	size_t chunckSize = ChunckManager::m_ChunckSize;

	for (size_t x = 0; x < chunckSize; x++)
	{
		for (size_t y = 0; y < chunckSize; y++)
		{
			for (size_t z = 0; z < chunckSize; z++)
			{
				//glm::vec3 voxelWorldCoord = glm::vec3(m_WorldChunckCoord.x + x, y, m_WorldChunckCoord.y + z);
				m_Blocks[x][y][z] = (rand() % 4);
			}
		}
	}
}

void Chunck::AddVoxelFaces(glm::vec3 localVoxelIndex)
{
	int chunckSize = ChunckManager::m_ChunckSize;

	glm::vec3 globalVoxelIndex = glm::vec3(m_GlobalChunckCoord.x * chunckSize + localVoxelIndex.x,
		localVoxelIndex.y,
		m_GlobalChunckCoord.y * chunckSize + localVoxelIndex.z);

	ChunckManager::Block currentBlock = GetBlock(localVoxelIndex);

	//Return if its air
	if (!currentBlock)
		return;

	bool visibleSides[]
	{
		(localVoxelIndex.y == chunckSize-1) ? 
			true : !GetBlock((glm::vec3) localVoxelIndex + Transform::up), //Top

		(localVoxelIndex.y == 0) ?
			true : !GetBlock(localVoxelIndex - Transform::up), //Bottom

		(localVoxelIndex.z == chunckSize - 1) ?
			!m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::forward) : !GetBlock(localVoxelIndex + Transform::forward), //Front

		(localVoxelIndex.z == 0) ?
			!m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::forward) : !GetBlock(localVoxelIndex - Transform::forward), //Back

		(localVoxelIndex.x == chunckSize - 1) ?
			!m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::right) : !GetBlock(localVoxelIndex + Transform::right), //Right

		(localVoxelIndex.x == 0) ?
			!m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::right) : !GetBlock(localVoxelIndex - Transform::right), //Left
	};

	size_t vertCount = m_Vertices.size();

	for (size_t i = 0; i < 6; i++)
	{
		if (!visibleSides[i])
			continue;

		for (size_t j = 0; j < 6; j++)
		{
			size_t vertIndex = vertCount + m_FaceTriangulation[j];
			m_Triangles.push_back(vertIndex);
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
			m_Vertices.push_back(vertex);
		}

		vertCount += 4;
	}
}

void Chunck::CreateChunckMesh()
{
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

	m_ChunckMesh.SetTriangles(&m_Triangles[0], m_Triangles.size());
	m_ChunckMesh.SetVertices(&m_Vertices[0], m_Vertices.size());
}

void Chunck::UpdateChunck() 
{
	m_ChunckTransform.m_Position = glm::vec3(m_WorldChunckCoord.x, 0, m_WorldChunckCoord.y);

	CreateChunckMesh();
}

ChunckManager::Block Chunck::GetBlock(glm::uvec3 localIndex)
{
	return m_Blocks[localIndex.x][localIndex.y][localIndex.z];
}

Chunck::~Chunck() {}

