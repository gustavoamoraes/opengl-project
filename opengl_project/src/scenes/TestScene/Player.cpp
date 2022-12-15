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
	glm::vec3 input(Input::GetKey(GLFW_KEY_D) - Input::GetKey(GLFW_KEY_A),
		Input::GetKey(GLFW_KEY_W) - Input::GetKey(GLFW_KEY_S),
		Input::GetKey(GLFW_KEY_Q) - Input::GetKey(GLFW_KEY_E));

	glm::vec3 rotation(0.0f, Input::GetKey(GLFW_KEY_N) - Input::GetKey(GLFW_KEY_M), 0.0f);

	m_Angle += rotation.y * 1 / 50.0f;

	m_MyScene->m_MainCamera.m_Transform.m_Rotation = glm::rotate(m_Angle, glm::vec3(1.0f, 0.0f, 0.0f));
	m_MyScene->m_MainCamera.m_Transform.m_Position += input * m_PlayerSpeed;

	Renderer::DrawMesh(m_Cube, m_PlayerTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

Player::~Player() {}

