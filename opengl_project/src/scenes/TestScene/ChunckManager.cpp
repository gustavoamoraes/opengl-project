#include <iostream>

#include "ChunckManager.h"
#include "Chunck.h"
#include "Application.h"

void ChunckManager::Start()
{
	GenerateChuncks();
}

ChunckManager::Block ChunckManager::getBlockGlobal(glm::vec3 globalVoxelIndex)
{
	if (globalVoxelIndex.x < 0 || globalVoxelIndex.y < 0 || globalVoxelIndex.z < 0 || globalVoxelIndex.y >= m_ChunckSize)
		return 0;

	glm::uvec2 chunckIndex = glm::vec2(floor(globalVoxelIndex.x / m_ChunckSize), floor(globalVoxelIndex.z / m_ChunckSize));

	if (chunckIndex.x >= m_ChuncksWidth || chunckIndex.y >= m_ChuncksHeight)
		return 0;

	glm::vec3 localVoxelCoord = glm::vec3(globalVoxelIndex.x - (chunckIndex.x * m_ChunckSize),
		globalVoxelIndex.y,
		globalVoxelIndex.z - (chunckIndex.y * m_ChunckSize));


	return m_Chuncks[chunckIndex.x][chunckIndex.y]->GetBlock(localVoxelCoord);
}

void ChunckManager::GenerateChuncks()
{
	for (size_t x = 0; x < m_ChuncksWidth; x++)
	{
		for (size_t y = 0; y < m_ChuncksHeight; y++)
		{
			Chunck* newChunck = new Chunck(glm::vec2(x, y));
			m_MyScene->AddEntity(newChunck);
			m_Chuncks[x][y] = newChunck;
			newChunck->GenerateChunckVoxels();
		}
	}
	
	for (size_t x = 0; x < m_ChuncksWidth; x++)
	{
		for (size_t y = 0; y < m_ChuncksHeight; y++)
		{
			m_Chuncks[x][y]->UpdateChunck();
		}
	}
}

ChunckManager::ChunckManager()
{
}

ChunckManager::~ChunckManager()
{
}
