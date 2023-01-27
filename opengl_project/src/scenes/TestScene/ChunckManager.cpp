#include <iostream>
#include <thread>

#include "Input.h"
#include "ChunckManager.h"
#include "Chunck.h"
#include "Application.h"
#include "TerrainGenerator.h"

void ChunckManager::Start()
{
	GenerateChuncks();

	for (size_t i = 0; i < 2; i++)
	{
		std::thread(&ChunckManager::GenerateChunck, this).detach();
	}

	for (size_t i = 0; i < 2; i++)
	{
		std::thread(&ChunckManager::UpdateChunck, this).detach();
	}
}

ChunckManager::BlockIndex ChunckManager::getBlockGlobal(glm::vec3 globalVoxelIndex)
{
	if (globalVoxelIndex.y < 0 || globalVoxelIndex.y >= m_ChunckSize.y)
		return 0;

	glm::vec2 chunckIndex = glm::vec2(floor(globalVoxelIndex.x / m_ChunckSize.x), floor(globalVoxelIndex.z / m_ChunckSize.z));

	if (!m_SpawnedChuncks.contains(chunckIndex))
		return 0;

	Chunck* chunck = m_SpawnedChuncks.at(chunckIndex);

	glm::vec3 localVoxelCoord = glm::vec3(
		globalVoxelIndex.x - (chunckIndex.x * m_ChunckSize.x),
		globalVoxelIndex.y,
		globalVoxelIndex.z - (chunckIndex.y * m_ChunckSize.z));

	return chunck->GetBlock(localVoxelCoord);
}

void ChunckManager::GenerateChuncks()
{
	std::vector<Chunck*> chuncksThatMayMakeBorder;

	for (Chunck* chunck : m_LastChuncks)
		chunck->SetActive(false);

	m_LastChuncks.clear();

	for (size_t y = 0; y < m_ChunckDistance; y++)
	{
		for (size_t x = 0; x < m_ChunckDistance; x++)
		{
			Chunck* newChunck = nullptr;

			glm::vec2 globalIndex = m_TargetChunckPosition - glm::ivec2(m_ChunckDistance)/2 + glm::ivec2(x,y);
			glm::vec3 chunckPosition = glm::vec3(globalIndex.x * m_ChunckSize.x, 0, globalIndex.y * m_ChunckSize.z);

			if (m_SpawnedChuncks.contains(globalIndex))
			{
				newChunck = m_SpawnedChuncks.at(globalIndex);
			}
			else
			{
				glm::vec2 previusPosition = globalIndex + m_TargetDisplacement;

				if (m_SpawnedChuncks.contains(previusPosition))
				{
					Chunck* previusChunckAtThisIndex = m_SpawnedChuncks.at(previusPosition);
					chuncksThatMayMakeBorder.push_back(previusChunckAtThisIndex);
				}

				newChunck = new Chunck(globalIndex, chunckPosition);

				m_Mutex3.lock();
				m_SpawnedChuncks.insert({ globalIndex , newChunck });
				m_Mutex3.unlock();

				m_ChuncksToGenerate.push(newChunck);
				m_ChuncksToUpdate.push(newChunck);
				m_MyScene->AddEntity(newChunck);
			}

			newChunck->SetActive(true);

			m_LastChuncks.push_back(newChunck);
		}
	}

	//for (Chunck* chunck : chuncksThatMayMakeBorder)
	//	if(chunck->m_Active) m_ChuncksToUpdate.push(chunck);
}

void ChunckManager::GenerateChunck()
{
	while (true)
	{
		while (m_ChuncksToGenerate.empty())
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

		Chunck* chunck = nullptr;

		{
			std::lock_guard<std::mutex> lockGuard(m_Mutex);

			if (m_ChuncksToGenerate.empty())
				continue;

			chunck = m_ChuncksToGenerate.front();
			m_ChuncksToGenerate.pop();
		}

		m_TerrainGenerator->GenerateVoxelsForChunck(chunck);
	}
}

void ChunckManager::UpdateChunck()
{
	while (true)
	{
		while (m_ChuncksToUpdate.empty())
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

		Chunck* chunck = nullptr;

		{
			std::lock_guard<std::mutex> lockGuard(m_Mutex2);

			if (m_ChuncksToUpdate.empty())
				continue;

			chunck = m_ChuncksToUpdate.front();

			glm::vec2 chunckIndex = chunck->m_GlobalChunckIndex;
			static glm::vec2 diretions[] { Transform::up, -Transform::up, Transform::right, -Transform::right };
			bool canUpdate = chunck->m_VoxelsReady && !chunck->m_UpdatingMesh;

			for (size_t i = 0; i < 4 && canUpdate; i++)
			{
				glm::vec2 neighborIndex = chunckIndex + diretions[i];

				m_Mutex3.lock();
				bool neighborChunckExists = m_SpawnedChuncks.count(chunckIndex + diretions[i]);
				m_Mutex3.unlock();

				canUpdate &= neighborChunckExists ? m_SpawnedChuncks.at(neighborIndex)->m_VoxelsReady : true;
			}

			if (!canUpdate)
				continue;

			m_ChuncksToUpdate.pop();
		}

		chunck->UpdateChunck();
	}
}

void ChunckManager::Update()
{
}

void ChunckManager::SetTarget(glm::vec2 target)
{
	glm::ivec2 newChunckPosition = { floor(target.x / ChunckManager::m_ChunckSize.x), 
		floor(target.y / ChunckManager::m_ChunckSize.z) };

	m_TargetDisplacement = (m_TargetChunckPosition - newChunckPosition);
	m_TargetChunckPosition = newChunckPosition;
	m_TargetPosition = target;
}

ChunckManager::ChunckManager() 
{
	srand((unsigned)time(NULL));
	unsigned int seed = rand()&UINT32_MAX;
	m_TerrainGenerator = new TerrainGenerator(123123u);
}

ChunckManager::~ChunckManager()
{
}
