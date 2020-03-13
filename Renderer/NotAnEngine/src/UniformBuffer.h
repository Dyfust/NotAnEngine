#include "Renderer.h"
#pragma once

class UniformBuffer
{
private:
	unsigned int _bufferID;
	unsigned int _bindingPoint;
	unsigned int _size;

public:
	UniformBuffer(unsigned int bindingPoint, unsigned int size, GLenum usage);
	~UniformBuffer();

	void UpdateBufferData(unsigned int offset, unsigned int size, const void* data);

	void Bind();
	void Unbind();
};