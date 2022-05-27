#include "Scene.h"
#include "ClearColorScene.h"
#include "Renderer.h"
#include "imgui/imgui.h"

scene::ClearColorScene::ClearColorScene() : color{ 1.0f, 0.2f, 0.3f, 1.0f }
{
}

scene::ClearColorScene::~ClearColorScene()
{
}

void scene::ClearColorScene::OnUpdate()
{
}

void scene::ClearColorScene::OnRender()
{
	GLCall(glClearColor(color[0], color[1], color[2], color[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void scene::ClearColorScene::OnImGUIRender()
{
	ImGui::Begin("Window A");
	ImGui::ColorEdit4("Background Color", color);
	ImGui::End();
}
