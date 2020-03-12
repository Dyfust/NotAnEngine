#include "Renderer.h"
#pragma once

class UniformBuffer
{
private:
	unsigned int _bufferID;
	unsigned int _bindingPoint;
	unsigned int _size;

public:
	UniformBuffer(unsigned int size, unsigned int bindingPoint, GLenum usage);
	~UniformBuffer();

	void UpdateBuffer(unsigned int offset, unsigned int size, const void* data);

	void Bind();
	void Unbind();
};