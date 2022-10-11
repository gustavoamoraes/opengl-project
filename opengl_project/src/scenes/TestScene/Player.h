#pragma once

#include "./scenes/Entity.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;
	//void Setup() override;

private:
	Shader m_Shader;

	const int m_PlaneWidthUnits = 1;
	const int m_PlaneDepthUnits = 1;

	glm::vec3 m_PlayerPosition;
	const float m_PlayerSpeed = 0.05f;

	VertexArray m_PlaneVertexArray;
	IndexBuffer* m_PlaneTrianglesBuffer;
	VertexBuffer* m_PlaneVerticesBuffer;
	VertexBufferLayout m_Layout;
};
