#include "Gui.h"
#include "Application.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

Gui::Gui()
{
}

Gui::~Gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Gui::Setup()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330 core");

	GLFWwindow* window = Application::GetInstance()->GetWindow().GetNativeWindow();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void Gui::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Gui::End()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
