#pragma once

#include <GLFW/glfw3.h>

enum class EventType { None, KeyUp, KeyDown, KeyRepeat };

class Event;

class Event
{
public:
	static Event current;

	static Event KeyEvent(int scanCode, int type);

	Event();
	Event(const Event& rhs);

	int keyCode;
	EventType type;
};