#include "Window.h"
#include "Events/MousePressEvent.h"
#include "Events/MouseReleaseEvent.h"
#include <iostream>

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	_width = width;
	_height = height;
	_title = title;

	_glfwWindowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (_glfwWindowPtr == nullptr)
	{
		std::cout << "GLFW failed to create window!" << std::endl;
	}

	/*glfwSetWindowUserPointer(_glfwWindowPtr, &_onEventCallback);
	glfwSetMouseButtonCallback(_glfwWindowPtr, [](GLFWwindow* window, int button, int action, int mods)
	{
		fn& callback = *(fn*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MousePressEvent p = MousePressEvent(button);
				callback(p);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseReleaseEvent r = MouseReleaseEvent(button);
				callback(r);
				break;
			}
		}
	});*/
}

Window::~Window()
{
	glfwDestroyWindow(_glfwWindowPtr);
}

void Window::SetOnEventCallback(fn callback)
{
	_onEventCallback = callback;
}

void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(_glfwWindowPtr);
}

void Window::Update()
{
	glfwSwapBuffers(_glfwWindowPtr);
}

GLFWwindow* Window::GetWindowPtr()
{
	return _glfwWindowPtr;
}

const char* Window::GetTitle() const
{
	return _title;
}

const unsigned int Window::GetWidth() const
{
	return _width;
}

const unsigned int Window::GetHeight() const
{
	return _height;
}
