#pragma once
#include "glfw3.h"

class Window
{
private:
	const char* _title;
	unsigned int _width;
	unsigned int _height;

	GLFWwindow* _glfwWindowPtr;

public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	void MakeContextCurrent();
	void Update();

	GLFWwindow* GetWindowPtr();
	const char* GetTitle() const;
	const unsigned int GetWidth() const;
	const unsigned int GetHeight() const;
};