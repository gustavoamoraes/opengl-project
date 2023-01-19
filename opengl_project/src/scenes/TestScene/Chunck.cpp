#include <malloc.h>  
#include <iostream>
#include <vector>

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

Chunck::Chunck(glm::vec2 chunckWorldCoord) : m_WorldChunckCoord(chunckWorldCoord), m_ChunckMesh(this)
{
	m_ChunckManager = ChunckManager::instance();
}

void Chunck::Update()
{
	if (!m_ChunckMesh.m_MeshApplied && m_MeshUpdateReady)
	{
		m_ChunckMesh.ApplyMesh();
		m_MeshUpdateReady = false;
	}

	Renderer::DrawMesh( m_ChunckMesh.m_Mesh, m_ChunckTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

void Chunck::Start()
{
	m_ChunckTransform.m_Position = glm::vec3(m_WorldChunckCoord.x * ChunckManager::m_ChunckSize.x, 0, m_WorldChunckCoord.y * ChunckManager::m_ChunckSize.z);
}

void Chunck::UpdateChunck() 
{
	m_MeshUpdateReady = false;

	m_ChunckMesh.UpdateChunckMesh();

	m_MeshUpdateReady = true;
}

ChunckManager::BlockIndex Chunck::GetBlock(glm::uvec3 localIndex) const
{
	return m_Blocks[localIndex.x][localIndex.y][localIndex.z];
}

Chunck::~Chunck() {}

