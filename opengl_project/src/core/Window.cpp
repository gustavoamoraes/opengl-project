#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Application.h"
#include "Event.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height) :
	m_Title(title), m_Width(width), m_Height(height)
{	
	glewExperimental = GL_TRUE;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
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

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Event::current = Event::KeyEvent(key, action);
	});

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
