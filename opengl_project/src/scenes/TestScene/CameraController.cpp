#include <iostream>
#include <thread>

#include "CameraController.h"
#include "Input.h"
#include "Chunck.h"

#include <GLFW/glfw3.h>

CameraController::CameraController() 
{
	m_LastMousePosition = glm::vec2(0.0f);
}

void CameraController::Start()
{
	m_MyScene->m_MainCamera.SetBackgroundColor({ 34, 128, 161 });

	m_ChunckManager = ChunckManager::instance();

	m_MyScene->m_MainCamera.m_Transform.m_Position = glm::vec3(0, 128, 0);
}

CameraController::~CameraController()
{
}

void CameraController::Update()
{
	glm::vec3 input(Input::GetKey(GLFW_KEY_D) - Input::GetKey(GLFW_KEY_A),
		Input::GetKey(GLFW_KEY_Q) - Input::GetKey(GLFW_KEY_E),
		Input::GetKey(GLFW_KEY_S) - Input::GetKey(GLFW_KEY_W));

	glm::vec2 mousePosNow = Input::GetMousePosition();
	glm::vec2 mousePosDifference = m_LastMousePosition - mousePosNow;

	m_Yaw += mousePosDifference.x * m_Sensitivity;
	m_Pitch += mousePosDifference.y * m_Sensitivity;

	Transform* cameraTransform = &m_MyScene->m_MainCamera.m_Transform;

	glm::mat4 rotationMat(1);
	rotationMat = glm::rotate(rotationMat, m_Yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMat = glm::rotate(rotationMat, m_Pitch, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::vec3 right = glm::vec3(rotationMat * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	glm::vec3 forward = glm::vec3(rotationMat * glm::vec4(0.0f, 0.0f, 1.0f, 1.0));

	cameraTransform->m_Position += m_Velocity * (forward * input.z + right * input.x);
	cameraTransform->m_Rotation = rotationMat;

	glm::vec2 chunckCoord = {floor(cameraTransform->m_Position.x / m_ChunckManager->m_ChunckSize.x),
		floor(cameraTransform->m_Position.z / m_ChunckManager->m_ChunckSize.z) };

	if (chunckCoord != m_LastChunckCoord)
	{ 	  
		m_ChunckManager->SetTarget({ cameraTransform->m_Position.x, cameraTransform->m_Position.z });
		m_ChunckManager->GenerateChuncks();
		m_LastChunckCoord = chunckCoord;
	}

	m_LastMousePosition = mousePosNow;
}