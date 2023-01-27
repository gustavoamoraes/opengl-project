#include <iostream>
#include <string>
#include <memory>
#include <typeinfo>

#include "Application.h"
#include "Renderer.h"
#include "scenes/TestScene/MainScene.h"
#include "Gui.h"
#include "Scene.h"
#include "Input.h"

#include "imgui/imgui.h"

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& name)
{
	s_Instance = this;

	m_Window = std::unique_ptr<Window>(new Window((std::string)name, 1600, 900));
	m_Gui = std::unique_ptr<Gui>(new Gui());
	m_CurrentScene = new MainScene();
}

void Application::Run()
{
	m_Gui->Setup();

	Renderer::Init();

	while (m_Running)
	{
		if(Input::GetKey(GLFW_KEY_ESCAPE))
			m_Running = false;

		if (!m_CurrentScene)
			break;

		Renderer::Clear();

		m_CurrentScene->OnNewEntities();
		m_CurrentScene->OnUpdate();

		//m_Gui->Begin();
		//m_CurrentScene->OnImGUIRender();
		//m_Gui->End();

		m_Window->OnUpdate();
	}
}

Window& Application::GetWindow()
{
	return *m_Window;
}

void Application::OnWindowClosed()
{	
	m_Running = false;
}

Application::~Application()
{
}
