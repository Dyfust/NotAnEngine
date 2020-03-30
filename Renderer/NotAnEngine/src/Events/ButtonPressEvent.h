#pragma once
#include "Event.h"
#include <utility>

class ButtonPressEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::ButtonPressEvent; }
	virtual EventType GetEventType() override { return EventType::ButtonPressEvent; }

	ButtonPressEvent(int button) : Event(), _button(button)
	{}
	~ButtonPressEvent()
	{}

	// Update this to return a Vector2 in the future.
	int GetButton()
	{
		return _button;
	}

private:
	int _button;
};