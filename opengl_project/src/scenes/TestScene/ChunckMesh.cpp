#include <iostream>

#include "ChunckMesh.h"
#include "ChunckManager.h"
#include "Chunck.h"
#include "Blocks.h"

ChunckMesh::ChunckMesh(Chunck* myChunck) : m_MyChunck(myChunck), m_Triangles(nullptr), m_Vertices(nullptr)
{
	m_ChunckManager = ChunckManager::instance();
}

ChunckMesh::~ChunckMesh()
{
}

void ChunckMesh::UpdateChunckMesh()
{
	m_MeshApplied = false;

	m_Triangles = (unsigned int*)malloc(ChunckManager::m_MaxExposedVoxels * 6 * 6 * sizeof(unsigned int));
	m_Vertices = (Mesh::Vertex*)malloc(ChunckManager::m_MaxExposedVoxels * 4 * 6 * sizeof(Mesh::Vertex));

	if (!m_Triangles || !m_Vertices)
		return;

	auto chunckSize = ChunckManager::m_ChunckSize;

	m_VerticeCount = 0;
	m_TriangleCount = 0;

	for (size_t x = 0; x < chunckSize.x; x++)
	{
		for (size_t y = 0; y < chunckSize.y; y++)
		{
			for (size_t z =0; z < chunckSize.z; z++)
			{
				AddVoxelFaces(glm::vec3(x, y, z));
			}
		}	
	}
}	

void ChunckMesh::ApplyMesh()
{
	if (!m_Triangles || !m_Vertices)
		return;

	m_Mesh.SetTriangles(m_Triangles, m_TriangleCount);
	m_Mesh.SetVertices(m_Vertices, m_VerticeCount);

	free(m_Triangles);
	free(m_Vertices);

	m_MeshApplied = true;
}

void ChunckMesh::AddVoxelFaces(glm::vec3 localVoxelIndex)
{
	ChunckManager::BlockIndex currentBlock = m_MyChunck->GetBlock(localVoxelIndex);

	if (currentBlock == Blocks::AIR.id)
		return;

	auto chunckSize = ChunckManager::m_ChunckSize;

	glm::vec3 globalVoxelIndex = glm::vec3
	(
		m_MyChunck->m_GlobalChunckIndex.x * chunckSize.x + localVoxelIndex.x,
		localVoxelIndex.y,
		m_MyChunck->m_GlobalChunckIndex.y * chunckSize.z + localVoxelIndex.z
	);

	bool visibleSides[6] { 0, 0, 0, 0, 0, 0 };

	visibleSides[(int)CubeSide::Top] = !m_MyChunck->GetBlock2(localVoxelIndex + Transform::up);
	visibleSides[(int)CubeSide::Bottom] = !m_MyChunck->GetBlock2(localVoxelIndex - Transform::up);
	visibleSides[(int)CubeSide::Front] = !m_MyChunck->GetBlock2(localVoxelIndex + Transform::forward);
	visibleSides[(int)CubeSide::Back] = !m_MyChunck->GetBlock2(localVoxelIndex - Transform::forward);
	visibleSides[(int)CubeSide::Right] = !m_MyChunck->GetBlock2(localVoxelIndex + Transform::right);
	visibleSides[(int)CubeSide::Left] = !m_MyChunck->GetBlock2(localVoxelIndex - Transform::right);

	for (size_t i = 0; i < 6; i++)
	{
		CubeSide side = (CubeSide)i;

		if (!visibleSides[i])
			continue;

		for (size_t j = 0; j < 6; j++)
		{
			size_t vertIndex = m_VerticeCount + m_FaceTriangulation[j];
			m_Triangles[m_TriangleCount + j] = vertIndex;
		}

		for (size_t j = 0; j < 4; j++)
		{
			Mesh::Vertex vertex;
			unsigned int vertexData = 0;

			int vertexIndex = m_FaceVerticeIndexes.at(side).indices[j];
			glm::uvec3 vertPosition = localVoxelIndex + m_CubeVertices[vertexIndex];

			vertexData |= vertPosition.x;
			vertexData |= vertPosition.y << 5;
			vertexData |= vertPosition.z << 12;

			int atlasIndex = Blocks::m_AllBlocks[currentBlock]->atlasIndices.at(side);

			vertexData |= atlasIndex << 17;
			vertexData |= j << 21;

			vertex.data = vertexData;
			m_Vertices[m_VerticeCount + j] = vertex;
		}

		m_VerticeCount += 4;
		m_TriangleCount += 6;
	}
}
