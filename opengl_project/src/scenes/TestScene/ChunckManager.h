#ifndef CHUNCK_MANAGER_H
#define CHUNCK_MANAGER_H

#include "Entity.h"
#include "CameraController.h"

class Chunck;
class ChunckMesh;
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

	//Number of voxels that give the max area possible. Number of voxel that dont have neighbors except in the diagonals. *approximately* 
	static const unsigned int m_MaxExposedVoxels = (m_ChunckSize.x * m_ChunckSize.y * m_ChunckSize.z * 1/2);

	BlockIndex getBlockGlobal(glm::vec3 globalVoxelIndex);
	void GenerateChuncks();
	void Start() override;

private:
	ChunckManager();
	~ChunckManager();

	TerrainGenerator* m_TerrainGenerator;

	static const size_t m_ChuncksWidth = 4;
	static const size_t m_ChuncksHeight = 4;

	Chunck* m_Chuncks[m_ChuncksWidth][m_ChuncksHeight];
};

#else
class ChunckManager;
#endif