#pragma once
#include "Event.h"
#include <utility>

class WindowResizeEvent : public Event
{
public:
	static EventType GetStaticEventType() { return EventType::WindowResizeEvent; }
	virtual EventType GetEventType() override { return EventType::WindowResizeEvent; }

	WindowResizeEvent(int sizeX, int sizeY) : Event(), _sizeX(sizeX), _sizeY(sizeY)
	{}

	~WindowResizeEvent()
	{}

	// Update this to return a Vector2 in the future.
	std::pair<float, float> GetSize()
	{
		std::pair<float, float> pair;
		pair.first = _sizeX;
		pair.second = _sizeY;

		return pair;
	}

private:
	int _sizeX;
	int _sizeY;
};