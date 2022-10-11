#include <malloc.h>  
#include <iostream>

#include "imgui/imgui.h"
#include "Player.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Player::Player() : m_Shader("res/shaders/basic_shader.shader")
{
	const int verticesCount = (m_PlaneWidthUnits + 1) * (m_PlaneDepthUnits + 1);
	const int triangleCount = m_PlaneWidthUnits * m_PlaneDepthUnits * 6;
	int triIndex = 0;

	float* planeVertices = (float*) malloc(sizeof(glm::vec3) * verticesCount);
	unsigned int* planeTriangles = (unsigned int*)malloc(sizeof(int) * triangleCount);

	auto getVerticeIndex = [this](int x, int y)
	{
		return (x * (m_PlaneDepthUnits+1)) + y;
	};

	for (int x = 0; x <= m_PlaneWidthUnits; x++)
	{
		for (int y = 0; y <= m_PlaneDepthUnits; y++)
		{
			glm::vec3 vertPosition(x, 0.0f, y);
			memcpy(planeVertices + (getVerticeIndex(x, y) * glm::vec3::length()), &vertPosition, sizeof(glm::vec3));

			if (x < m_PlaneWidthUnits && y < m_PlaneDepthUnits)
			{
				planeTriangles[triIndex] = getVerticeIndex(x, y);
				planeTriangles[triIndex + 1] = getVerticeIndex(x, y + 1);
				planeTriangles[triIndex + 2] = getVerticeIndex(x + 1, y + 1);

				planeTriangles[triIndex + 3] = getVerticeIndex(x, y);
				planeTriangles[triIndex + 4] = getVerticeIndex(x + 1, y + 1);
				planeTriangles[triIndex + 5] = getVerticeIndex(x + 1, y);

				triIndex += 6;
			}
		}
	}

	m_Layout.Push<float>(3);

	m_PlaneTrianglesBuffer = new IndexBuffer(planeTriangles, triangleCount);
	m_PlaneVerticesBuffer = new VertexBuffer(planeVertices, verticesCount * sizeof(glm::vec3));

	m_PlaneVertexArray.Bind();

	m_PlaneVertexArray.AddBuffer(m_Layout, *m_PlaneVerticesBuffer);
	m_PlaneVertexArray.SetIndexBuffer(*m_PlaneTrianglesBuffer);

	m_PlayerPosition = glm::vec3(0.0f, 2.0f, -7.0f);
}

void Player::Update()
{	
	glm::vec3 input(Input::GetKey(GLFW_KEY_D) - Input::GetKey(GLFW_KEY_A), 
		Input::GetKey(GLFW_KEY_W) - Input::GetKey(GLFW_KEY_S), 
		Input::GetKey(GLFW_KEY_Q) - Input::GetKey(GLFW_KEY_E));

	m_PlayerPosition -= input * m_PlayerSpeed;

	glm::mat4 proj = glm::perspective(45.0f, 1.33f, 0.0f, 300.0f);
	glm::mat4 model = glm::translate(m_PlayerPosition);

	glm::mat4 mvp = proj * model;

	m_Shader.Bind();
	m_Shader.SetUniforms4f("u_Color", .5f, 0.0f, .5f, 0.0f);
	m_Shader.SetUniformsMat4f("u_MVP", mvp);

	Renderer::Draw(m_Shader, m_PlaneVertexArray, m_PlaneVertexArray.GetIndexBuffer()->m_IndexCount);
}

Player::~Player()
{
}
