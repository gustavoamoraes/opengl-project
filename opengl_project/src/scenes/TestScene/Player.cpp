#include <malloc.h>  
#include <iostream>
#include <vector>

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
	m_MyScene->m_MainCamera.SetBackgroundColor({ 34, 128, 161 });

	m_TextureTest = new Texture("res/textures/c.png");

	m_TextureTest->Bind();

	/*glm::vec3 vertices[]
	{
		glm::vec3(0.5f,  0.5f, 0.5f),
		glm::vec3(-0.5f,  0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),

		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
	};*/

	Mesh::Vertex vertices[]
	{
		glm::vec3(0.0f,  0.0f, 0.0f), glm::vec2(0.0f,0.0f),
		glm::vec3(1.0f,  0.0f, 0.0f), glm::vec2(1.0f,0.0f),	
		glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f,1.0f),
		glm::vec3(0.0f, 0.0f, 2.0f), glm::vec2(0.0f, 2.0f),
		glm::vec3(1.0f, 0.0f, 2.0f), glm::vec2(1.0f,2.0f)
	};

	unsigned int triangles[] { 0,1,2,2,1,3, 2,3,4,4,3,5 };
	
	/*std::vector<unsigned int> triangles;

	int verticeIndicies[]{0,1,2,3,4,5,6,7};
	bool visibleSides[] {true, true, true, false, false, true };

	for (size_t i = 0; i < 6; i++)
	{
		if (!visibleSides[i])
			continue;

		for (size_t j = 0; j < 6; j++)
		{
			int index = m_Sides[i][j];
			triangles.push_back(verticeIndicies[index]);
		}
	}*/

	m_Cube.SetTriangles(&triangles[0], 6*2);
	m_Cube.SetVertices(&vertices[0], 6);
}

void Player::Update()
{
	Renderer::DrawMesh(m_Cube, m_PlayerTransform.GetMatrix(), m_MyScene->m_MainCamera.getViewProjectionMatrix());
}

Player::~Player() {}

