#pragma once
#include "Event.h"
#include <utility>

class ButtonRepeatEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::ButtonRepeatEvent; }
	virtual EventType GetEventType() override { return EventType::ButtonRepeatEvent; }

	ButtonRepeatEvent(int button, int repeatCount) : Event(), _button(button), _repeatCount(repeatCount)
	{}

	~ButtonRepeatEvent()
	{}

	// Update this to return a Vector2 in the future.
	int GetButton()
	{ return _button; }

	int GetRepeatCount()
	{ return _repeatCount; }

private:
	int _button;
	int _repeatCount;
};