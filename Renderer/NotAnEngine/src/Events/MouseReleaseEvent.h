#pragma once
#include "Event.h"
#include <utility>

class MouseReleaseEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::MouseReleaseEvent; }
	virtual EventType GetEventType() override { return EventType::MouseReleaseEvent; }

	MouseReleaseEvent(int button) : Event(), _button(button)
	{}
	~MouseReleaseEvent()
	{}

	int GetButton() { return _button; }

private:
	int _button;
};