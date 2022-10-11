#include "Event.h"

Event::Event() : keyCode(-1), type(EventType::None)
{
}

Event::Event(const Event& rhs)
{
	keyCode = rhs.keyCode;
	type = rhs.type;
}

Event Event::KeyEvent(int scanCode, int action)
{
	Event newKeyEvent = Event();

	newKeyEvent.keyCode = scanCode;
	
	switch (action)
	{
		case GLFW_PRESS:
		{
			newKeyEvent.type = EventType::KeyDown;
			break;
		}
		case GLFW_RELEASE:
		{
			newKeyEvent.type = EventType::KeyUp;
			break;
		}
		case GLFW_REPEAT:
		{
			newKeyEvent.type = EventType::KeyRepeat;
			break;
		}
	}

	return newKeyEvent;
}

Event Event::current;