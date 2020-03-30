#pragma once
#include "Event.h"
#include <utility>

class MouseMovedEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::MouseMovedEvent; }
	EventType GetEventType() override { return EventType::MouseMovedEvent; }

	MouseMovedEvent(float cursorX, float cursorY) : Event(), _cursorX(cursorX), _cursorY(cursorY)
	{}
	~MouseMovedEvent()
	{}

	// Update this to return a Vector2 in the future.
	std::pair<float, float> GetPosition()
	{
		std::pair<float, float> pair;
		pair.first = _cursorX;
		pair.second = _cursorY;

		return pair;
	}

private:
	float _cursorX;
	float _cursorY;
};