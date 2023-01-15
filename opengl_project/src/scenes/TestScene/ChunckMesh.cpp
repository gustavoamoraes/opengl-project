#include "ChunckMesh.h"
#include "ChunckManager.h"
#include "Chunck.h"
#include "Blocks.h"

ChunckMesh::ChunckMesh(Chunck* myChunck) : m_MyChunck(myChunck)
{
	m_ChunckManager = ChunckManager::instance();
}

ChunckMesh::~ChunckMesh()
{
}

void ChunckMesh::UpdateChunckMesh()
{
	m_Triangles = (unsigned int*) malloc(ChunckManager::m_MaxExposedVoxels * 6 * 6 * sizeof(unsigned int));
	m_Vertices = (Mesh::Vertex*) malloc(ChunckManager::m_MaxExposedVoxels * 4 * 6 * sizeof(Mesh::Vertex));

	auto chunckSize = ChunckManager::m_ChunckSize;

	for (size_t x = 0; x < chunckSize.x; x++)
	{
		for (size_t y = 0; y < chunckSize.y; y++)
		{
			for (size_t z = 0; z < chunckSize.z; z++)
			{
				AddVoxelFaces(glm::vec3(x, y, z));
			}
		}
	}

	m_Mesh.SetTriangles(m_Triangles, m_TriangleCount);
	m_Mesh.SetVertices(m_Vertices, m_VerticeCount);

	free(m_Triangles);
	free(m_Vertices);
}

void ChunckMesh::AddVoxelFaces(glm::vec3 localVoxelIndex)
{
	ChunckManager::BlockIndex currentBlock = m_MyChunck->GetBlock(localVoxelIndex);

	//Return if its air
	if (!currentBlock)
		return;

	auto chunckSize = ChunckManager::m_ChunckSize;

	glm::vec3 globalVoxelIndex = glm::vec3
	(
		m_MyChunck->m_WorldChunckCoord.x * chunckSize.x + localVoxelIndex.x,
		localVoxelIndex.y,
		m_MyChunck->m_WorldChunckCoord.y * chunckSize.z + localVoxelIndex.z
	);

	bool visibleSides[6] { false, false, false, false, false, false };

	visibleSides[(int)CubeSide::Top] = !m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::up);
	visibleSides[(int)CubeSide::Bottom] = !m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::up);
	visibleSides[(int)CubeSide::Front] = !m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::forward);
	visibleSides[(int)CubeSide::Back] = !m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::forward);
	visibleSides[(int)CubeSide::Right] = !m_ChunckManager->getBlockGlobal(globalVoxelIndex + Transform::right);
	visibleSides[(int)CubeSide::Left] = !m_ChunckManager->getBlockGlobal(globalVoxelIndex - Transform::right);

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
