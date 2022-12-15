#pragma once

#include "Transform.h"

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

private:
	float m_Fovy = 45.0f;
	float m_Far = 300.0f;
	float m_Near = 0.0f;
	float m_Aspect = 4.0f / 3.0f;
};