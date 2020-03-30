#pragma once
#include "Event.h"
#include <utility>

class ButtonReleaseEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::ButtonReleaseEvent; }
	virtual EventType GetEventType() override { return EventType::ButtonReleaseEvent; }

	ButtonReleaseEvent(int button, int repeatCount) : Event(), _button(button)
	{}

	~ButtonReleaseEvent()
	{}

	// Update this to return a Vector2 in the future.
	int GetButton()
	{
		return _button;
	}

private:
	int _button;
};