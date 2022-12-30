#pragma once

#include "Entity.h"
#include "Renderer.h"
#include "Shader.h"
#include "Transform.h"
#include "VertexArray.h"
#include "Texture.h"

class Chunck : public Entity
{
public:
	Chunck();
	~Chunck();

	void Update() override;

private:

	const int m_FaceTriangulation[6]{ 3,1,0,3,2,1 };

	const int m_FaceVerticeIndexes[6][4]
	{
		{0,1,2,3}, //Top
		{7,6,5,4}, //Bottom
		{3,2,6,7}, //Front
		{1,0,4,5}, //Back
		{2,1,5,6}, //Right
		{0,3,7,4}, //Left
	};

	const glm::vec3 m_CubeVertices[8]
	{
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	const int m_PlaneWidthUnits = 1;
	const int m_PlaneDepthUnits = 1;
	float m_Angle = 0;
	TextureArray* m_TextureTest;
	Transform m_PlayerTransform;
	Transform m_TestTransform;
	Mesh m_Cube;
};
