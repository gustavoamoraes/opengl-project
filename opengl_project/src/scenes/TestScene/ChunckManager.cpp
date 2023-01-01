#include "ChunckManager.h"
#include "Chunck.h"
#include "Application.h"

void ChunckManager::Start()
{
	GenerateChuncks();
}

ChunckManager::Block ChunckManager::getBlockGlobal(glm::uvec3 globalVoxelIndex)
{
	glm::uvec2 chunckIndex = glm::vec2(floor(globalVoxelIndex.x / m_ChunckSize), floor(globalVoxelIndex.z / m_ChunckSize));

	if ( (chunckIndex.x+1) >= m_ChuncksWidth && (chunckIndex.y+1) >= m_ChuncksHeight)
		return 0;

	glm::uvec3 localVoxelCoord = glm::vec3(globalVoxelIndex.x - (chunckIndex.x * m_ChunckSize),
		globalVoxelIndex.y,
		globalVoxelIndex.z - (chunckIndex.y * m_ChunckSize));

	return m_Chuncks[chunckIndex.x][chunckIndex.y]->GetBlock(localVoxelCoord);
}

void ChunckManager::GenerateChuncks()
{
	Chunck* newChunck = new Chunck(glm::vec3(0, 0, 0));
	m_MyScene->AddEntity(newChunck);
	m_Chuncks[0][0] = newChunck;
}

ChunckManager::ChunckManager()
{
}

ChunckManager::~ChunckManager()
{
}
