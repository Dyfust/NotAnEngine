#pragma once
#include <string>
#include "Renderer.h"

class Texture
{
private:
	unsigned int _textureID;
	int _width;
	int _height;
	int _nrChannels;

	unsigned char* _localBuffer;

public:
	Texture(const char* path);
	~Texture();

	void Bind(unsigned int slot);
	void Unbind();
};

