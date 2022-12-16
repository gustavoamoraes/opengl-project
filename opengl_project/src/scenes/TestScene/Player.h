#pragma once

#include "Entity.h"
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

private:
	const int m_PlaneWidthUnits = 1;
	const int m_PlaneDepthUnits = 1;
	float m_Angle = 0;
	Transform m_PlayerTransform;
	Transform m_TestTransform;
	Mesh m_Cube;
};
