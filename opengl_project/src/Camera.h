#pragma once

#include "Transform.h"

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Transform m_Transform;

	Camera() {};
	~Camera() {};

	glm::mat4 getViewProjectionMatrix()
	{
		return glm::perspective(m_Fovy, m_Aspect, m_Near, m_Far) * glm::inverse(m_Transform.GetMatrix());
	}

	//RGB: 0 -> 255
	void SetBackgroundColor(glm::ivec3 color)
	{
		glClearColor(color.r/ 255.0f, color.g/ 255.0f, color.b/255.0f, 1.0f);
	}

private:
	float m_Fovy = 45.0f;
	float m_Far = 300.0f;
	float m_Near = 0.1f;
	float m_Aspect = 16.0 / 9.0f;
};