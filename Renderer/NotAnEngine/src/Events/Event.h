#pragma once
class Event
{
public:
	enum class EventType
	{
		MousePressEvent, MouseReleaseEvent, MouseMovedEvent, 
		ButtonPressEvent, ButtonRepeatEvent, ButtonReleaseEvent,
		WindowResizeEvent
	};

	Event() { _handled = false; }
	~Event() {}

	virtual EventType GetEventType() = 0;
protected:
	friend class EventDispatcher;
	bool _handled;
};