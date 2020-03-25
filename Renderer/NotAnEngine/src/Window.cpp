#include "Window.h"
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
}

Window::~Window()
{
	glfwDestroyWindow(_glfwWindowPtr);
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
