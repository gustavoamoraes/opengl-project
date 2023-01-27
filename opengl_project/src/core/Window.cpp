#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Application.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height) :
	m_Title(title), m_Width(width), m_Height(height)
{	
	glewExperimental = GL_TRUE;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit())
		ASSERT(false);

	m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);


	if (!m_Window)
	{
		glfwTerminate();
		ASSERT(false);
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);

	//Set event callbacks
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		Application::GetInstance()->OnWindowClosed();
	});

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();
}

GLFWwindow* Window::GetNativeWindow()
{
	return m_Window;
}

void Window::OnUpdate()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::SetVSync(bool enabled)
{
	glfwSwapInterval(enabled ? 1 : 0);
}
