#ifndef CHUNCK_H
#define CHUNCK_H

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
	Chunck(glm::vec2 chunckWorldCoord);
	~Chunck();

	void Update() override;
	void Start() override;

	void UpdateChunck();

	ChunckManager::BlockIndex GetBlock(glm::uvec3 localIndex) const;
	ChunckMesh m_ChunckMesh;
	bool m_MeshUpdateReady = false;

private:
	ChunckManager::BlockIndex m_Blocks 
		[ChunckManager::m_ChunckSize.x]
		[ChunckManager::m_ChunckSize.y]
		[ChunckManager::m_ChunckSize.z];

	ChunckManager* m_ChunckManager;

	glm::vec2 m_WorldChunckCoord;
	Transform m_ChunckTransform;

friend TerrainGenerator;
friend ChunckMesh;
};

#else
class Chunck;
#endif