#pragma once
#include "Event.h"
#include <functional>

class EventDispatcher 
{
public:
	EventDispatcher(Event& event) : _event(event)
	{}

	~EventDispatcher() 
	{}

	template <typename T>
	void Dispatch(std::function<bool(T&)> func)
	{
		if (_event.GetEventType() == T::GetStaticEventType())
			_event._handled = func((T&)_event);
	}

private:
	Event& _event;
};