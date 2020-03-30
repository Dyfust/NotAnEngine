#pragma once
#include "Event.h"
#include <utility>

class MousePressEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::MousePressEvent; }
	virtual EventType GetEventType() override { return EventType::MousePressEvent; }

	MousePressEvent(int button) : Event(), _button(button)
	{}
	~MousePressEvent()
	{}

	int GetButton() { return _button; }

private:
	int _button;
};