#include "Input.h"
#include "Application.h"

bool Input::GetKey(int key)
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetNativeWindow();
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 Input::GetMousePosition() 
{
	GLFWwindow* window = Application::GetInstance()->GetWindow().GetNativeWindow();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return glm::vec2(xpos, ypos);
}





