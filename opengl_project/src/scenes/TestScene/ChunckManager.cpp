#include <iostream>

#include "ChunckManager.h"
#include "Chunck.h"
#include "Application.h"
#include "TerrainGenerator.h"

void ChunckManager::Start()
{
	GenerateChuncks();
}

ChunckManager::BlockIndex ChunckManager::getBlockGlobal(glm::vec3 globalVoxelIndex)
{
	if (globalVoxelIndex.x < 0 || globalVoxelIndex.y < 0 || globalVoxelIndex.z < 0 || globalVoxelIndex.y >= m_ChunckSize.y)
		return 0;

	glm::uvec2 chunckIndex = glm::vec2(floor(globalVoxelIndex.x / m_ChunckSize.x), floor(globalVoxelIndex.z / m_ChunckSize.z));

	if (chunckIndex.x >= m_ChuncksWidth || chunckIndex.y >= m_ChuncksHeight)
		return 0;

	glm::vec3 localVoxelCoord = glm::vec3(
		globalVoxelIndex.x - (chunckIndex.x * m_ChunckSize.x),
		globalVoxelIndex.y,
		globalVoxelIndex.z - (chunckIndex.y * m_ChunckSize.z));

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
			m_TerrainGenerator->GenerateVoxelsForChunck(newChunck);
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
	//srand((unsigned)time(NULL));
	//unsigned int seed = rand()&UINT32_MAX;
	//std::cout << seed;
	m_TerrainGenerator = new TerrainGenerator(23681u);
}

ChunckManager::~ChunckManager()
{
}
