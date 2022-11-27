#include <malloc.h>  
#include <iostream>

#include "imgui/imgui.h"
#include "Player.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Input.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

Player::Player() {}

void Player::Update()
{	
	glm::vec3 input(Input::GetKey(GLFW_KEY_D) - Input::GetKey(GLFW_KEY_A), 
		Input::GetKey(GLFW_KEY_W) - Input::GetKey(GLFW_KEY_S), 
		Input::GetKey(GLFW_KEY_Q) - Input::GetKey(GLFW_KEY_E));

	m_PlayerTransform.m_Position += input * m_PlayerSpeed;
	m_PlayerTransform.LookAt(glm::vec3(0.0f, 0.0f, 1.0f));
	
	Renderer::DrawQuad(m_PlayerTransform.GetMatrix());
}

Player::~Player() {}

