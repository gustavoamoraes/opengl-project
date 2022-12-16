#include <malloc.h>  
#include <iostream>

#include "imgui/imgui.h"
#include "Player.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Player::Player()
{
	Mesh::Vertex vertices[]
	{
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f,  0.5f, 0.0f),
		glm::vec3(-0.5f,  0.5f, 0.0f)
	};

	unsigned int triangles[]{ 0,1,2,2,3,0 };

	m_Cube.SetTriangles(triangles, 6);
	m_Cube.SetVertices(vertices, 4);
}

void Player::Update()
{
	Renderer::DrawMesh(m_Cube, m_PlayerTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

Player::~Player() {}

