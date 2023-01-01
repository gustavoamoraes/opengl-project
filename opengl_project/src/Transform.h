#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	static constexpr glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 GetMatrix() const;

	Transform();
	~Transform();

	void LookAt(glm::vec3 dir);
};