#pragma once

#include "./scenes/Entity.h"
#include "Renderer.h"
#include "Shader.h"
#include "Transform.h"
#include "VertexArray.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;
	//void Setup() override;

private:
	const int m_PlaneWidthUnits = 1;
	const int m_PlaneDepthUnits = 1;

	Transform m_PlayerTransform;
	const float m_PlayerSpeed = 0.05f;
};
