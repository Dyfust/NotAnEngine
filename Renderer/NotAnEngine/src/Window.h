#pragma once
#include "glfw3.h"
#include "Events/Event.h"
#include <functional>

class Window
{
private:
	const char* _title;
	unsigned int _width;
	unsigned int _height;

	GLFWwindow* _glfwWindowPtr;

	typedef std::function<void(Event&)> fn;
	fn _onEventCallback;

public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	void SetOnEventCallback(fn callback);
	void MakeContextCurrent();
	void Update();

	GLFWwindow* GetWindowPtr();
	const char* GetTitle() const;
	const unsigned int GetWidth() const;
	const unsigned int GetHeight() const;
};