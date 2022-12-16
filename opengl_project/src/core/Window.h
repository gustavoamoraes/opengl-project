#pragma once

#include <string>
#include <functional>
#include <GL/glew.h>
#include "GLFW/glfw3.h"

class Window
{
public:

	Window(const std::string& title, unsigned width, unsigned int height);
	~Window();

	void SetVSync(bool enabled);
	void SetOnEventCallback(const std::function<void(int, void*)> cb) { m_Data.m_OnEventCallback = cb; };
	GLFWwindow* GetNativeWindow();
	void OnUpdate();

	unsigned int m_Width;
	unsigned int m_Height;
	
private:

	struct WindowData
	{
		std::function<void(int, void*)> m_OnEventCallback;
	};

	GLFWwindow* m_Window;
	const std::string m_Title;
	WindowData m_Data;
};