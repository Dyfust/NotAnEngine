#include "UniformBuffer.h"

void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _bufferID);
}

void UniformBuffer::Unbind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::UniformBuffer(unsigned int bindingPoint, unsigned int size, GLenum usage)
{
	_bindingPoint = bindingPoint;
	_size = size;

	glGenBuffers(1, &_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, _bufferID);
	glBufferData(GL_UNIFORM_BUFFER, _size, NULL, usage);
	glBindBufferBase(GL_UNIFORM_BUFFER, _bindingPoint, _bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, _bindingPoint, 0);
	glDeleteBuffers(1, &_bufferID);
}

void UniformBuffer::UpdateBuffer(unsigned int offset, unsigned int size, const void* data)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	Unbind();
}