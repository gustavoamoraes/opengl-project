#pragma once

#include <map>
#include <glm/glm.hpp>

enum KeyCode { W = 0x1D, S = 0x1B };

class Input
{
public:
	static bool GetKey(int code);
	static glm::vec2 GetMousePosition();
};