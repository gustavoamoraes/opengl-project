#pragma once
#include <map>

enum KeyCode { W = 0x1D, S = 0x1B };

class Input
{
public:
	Input();
	static bool GetKey(int code);
};