#include <malloc.h>  
#include <iostream>
#include <vector>
#include <thread>

#include "Chunck.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"
#include "Transform.h"
#include "ChunckManager.h"

#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Chunck::Chunck(glm::vec2 chunckIndex, glm::vec3 worldPosition) : m_GlobalChunckIndex(chunckIndex), m_WorldChunckPosition(worldPosition), m_ChunckMesh(this)
{
	m_ChunckManager = ChunckManager::instance();
}

void Chunck::Update()
{
	if (!m_ChunckMesh.m_MeshApplied && m_MeshUpdateReady)
	{
		m_ChunckMesh.ApplyMesh();

		m_MeshUpdateReady = false;
		m_UpdatingMesh = false;
	}

	if (!m_Active)
		return;

	Renderer::DrawMesh( m_ChunckMesh.m_Mesh, m_ChunckTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

void Chunck::Start()
{
	m_ChunckTransform.m_Position = glm::vec3(m_WorldChunckPosition.x, 0, m_WorldChunckPosition.z);
}

void Chunck::UpdateChunck()
{
	m_UpdatingMesh = true;

	m_Neighbors[1][1] = this;

	m_Neighbors[0][1] = m_ChunckManager->m_SpawnedChuncks.contains(m_GlobalChunckIndex + glm::vec2(-1, 0)) ?
		m_ChunckManager->m_SpawnedChuncks.at(m_GlobalChunckIndex + glm::vec2(-1, 0)) : nullptr;

	m_Neighbors[2][1] = m_ChunckManager->m_SpawnedChuncks.contains(m_GlobalChunckIndex + glm::vec2(1, 0)) ?
		m_ChunckManager->m_SpawnedChuncks.at(m_GlobalChunckIndex + glm::vec2(1, 0)) : nullptr;

	m_Neighbors[1][0] = m_ChunckManager->m_SpawnedChuncks.contains(m_GlobalChunckIndex + glm::vec2(0, -1)) ?
		m_ChunckManager->m_SpawnedChuncks.at(m_GlobalChunckIndex + glm::vec2(0, -1)) : nullptr;

	m_Neighbors[1][2] = m_ChunckManager->m_SpawnedChuncks.contains(m_GlobalChunckIndex + glm::vec2(0, 1)) ?
		m_ChunckManager->m_SpawnedChuncks.at(m_GlobalChunckIndex + glm::vec2(0, 1)) : nullptr;

	m_ChunckMesh.UpdateChunckMesh();

	m_MeshUpdateReady = true;
}

void Chunck::SetChunckIndex(const glm::vec2 newIndex)
{
	m_GlobalChunckIndex = newIndex;
}

ChunckManager::BlockIndex Chunck::GetBlock(glm::ivec3 localIndex)
{
	return m_Blocks[localIndex.x][localIndex.y][localIndex.z];
}

ChunckManager::BlockIndex Chunck::GetBlock2(glm::ivec3 index)
{
	if (index.y >= ChunckManager::m_ChunckSize.y || index.y < 0)
		return 0;

	int x = (index.x >= (int) ChunckManager::m_ChunckSize.x) - (index.x < 0);
	int y = (index.z >= (int) ChunckManager::m_ChunckSize.z) - (index.z < 0);

	if (x == 0 && y == 0) return GetBlock(index);

	Chunck* chunck = m_Neighbors[1 + x][1 + y];

	if (!chunck)
		return 0;

	glm::vec3 localVoxelCoord = glm::vec3(
		index.x - (x * ChunckManager::m_ChunckSize.x),
		index.y,
		index.z - (y * ChunckManager::m_ChunckSize.z));

	return chunck->GetBlock(localVoxelCoord);
}

Chunck::~Chunck() {}

