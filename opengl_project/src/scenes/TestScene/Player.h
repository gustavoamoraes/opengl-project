#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "Shader.h"
#include "Transform.h"
#include "VertexArray.h"
#include "Texture.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Update() override;

private:

	const int m_Sides[6][6]
	{
		{0,1,2,2,1,3}, //Top
		{6,7,5,6,5,4}, //Bottom
		{5,4,0,5,0,1}, //Front
		{7,1,3,7,5,1}, //Left
		{6,3,2,6,7,3}, //Back
		{4,6,2,4,2,0}, //Right
	};

	const int m_PlaneWidthUnits = 1;
	const int m_PlaneDepthUnits = 1;
	float m_Angle = 0;
	Texture* m_TextureTest;
	Transform m_PlayerTransform;
	Transform m_TestTransform;
	Mesh m_Cube;
};
