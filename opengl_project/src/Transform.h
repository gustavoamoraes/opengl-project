#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 GetMatrix() const;

	Transform();
	~Transform();

	void LookAt(glm::vec3 dir);
};