#pragma once
#include <string>
#include "Renderer.h"

class Texture
{
private:
	unsigned int _textureID;
	unsigned int _slot;
	int _width;
	int _height;
	int _nrChannels;

	unsigned char* _localBuffer;

public:
	Texture(std::string& path, unsigned int slot = 0);
	~Texture();

	void Bind();
	void Unbind();
};

