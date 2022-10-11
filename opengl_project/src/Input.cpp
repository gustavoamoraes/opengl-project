#include "Input.h"
#include "Application.h"

Input::Input()
{
}

bool Input::GetKey(int key)
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetNativeWindow();
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}
