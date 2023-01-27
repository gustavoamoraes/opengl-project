#ifndef CHUNCK_MANAGER_H
#define CHUNCK_MANAGER_H

#include <map>
#include <queue>
#include <mutex>

#include "Entity.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

class Chunck;
class CameraController;
class TerrainGenerator;

class ChunckManager : public Entity
{
public:
	typedef unsigned char BlockIndex;

	static ChunckManager* instance()
	{
		static ChunckManager INSTANCE;
		return &INSTANCE;
	}

	static constexpr glm::uvec3 m_ChunckSize { 31,127,31 };
	static const unsigned int m_MaxExposedVoxels = (m_ChunckSize.x * m_ChunckSize.y * m_ChunckSize.z * 1/4);
	bool m_AllChuncksReady = false;

	BlockIndex getBlockGlobal(glm::vec3 globalVoxelIndex);

	void SetTarget(glm::vec2 target);
	void GenerateChuncks();
	void GeneratingWorker();
	void UpdatingWorker();

	void Start() override;
	void Update() override;

private:
	ChunckManager();
	~ChunckManager();

	TerrainGenerator* m_TerrainGenerator;

	std::mutex m_ChunckMapMutex;
	std::unordered_map<glm::vec2, Chunck*> m_SpawnedChuncks;

	std::mutex m_GenerateQueueMutex;
	std::queue<Chunck*> m_ChuncksToGenerate;

	std::mutex m_UpdateQueueMutex;
	std::queue<Chunck*> m_ChuncksToUpdate;

	glm::vec2 m_TargetPosition;
	glm::ivec2 m_TargetChunckPosition;
	glm::vec2 m_TargetDisplacement;

	static const size_t m_ChunckDistance = 16;

	std::vector<Chunck*> m_LastChuncks;

friend CameraController;
friend Chunck;
};

#else
class ChunckManager;
#endif