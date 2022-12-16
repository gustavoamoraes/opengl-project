#pragma once

#include "Entity.h"

class CameraController : public Entity
{
	public:
		CameraController();
		~CameraController();

		void Update() override;
	private:
		glm::vec2 m_LastMousePosition;

		float m_Yaw = 0;
		float m_Pitch = 0;
		const float m_Sensitivity = 0.001f;
		const float m_Velocity = 0.05f;
};