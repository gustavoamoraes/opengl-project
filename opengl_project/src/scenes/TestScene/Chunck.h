#ifndef CHUNCK_H
#define CHUNCK_H

#include <mutex>

#include "Entity.h"
#include "Renderer.h"
#include "Shader.h"
#include "Transform.h"
#include "VertexArray.h"
#include "TextureAtlas.h"
#include "ChunckManager.h"
#include "ChunckMesh.h"

class TerrainGenerator;

class Chunck : public Entity
{

public:
	Chunck(glm::vec2 chunckIndex, glm::vec3 worldPosition);
	~Chunck();

	void Update() override;
	void Start() override;

	void UpdateChunck();
	void SetChunckIndex(const glm::vec2 newIndex);

	ChunckManager::BlockIndex GetBlock(glm::ivec3 localIndex);
	ChunckManager::BlockIndex GetBlock2(glm::ivec3 localIndex);
	ChunckMesh m_ChunckMesh;

	bool m_MeshUpdateReady = false;
	bool m_VoxelsReady = false;
	bool m_UpdatingMesh = false;

	glm::vec2 m_GlobalChunckIndex;
	glm::vec3 m_WorldChunckPosition;
private:
	ChunckManager::BlockIndex m_Blocks 
		[ChunckManager::m_ChunckSize.x]
		[ChunckManager::m_ChunckSize.y]
		[ChunckManager::m_ChunckSize.z];

	Chunck* m_Neighbors [3][3];

	ChunckManager* m_ChunckManager;
	Transform m_ChunckTransform;

friend TerrainGenerator;
friend ChunckMesh;
};

#else
class Chunck;
#endif