#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* path)
{
	// Parse texture file.
	_localBuffer = stbi_load(path, &_width, &_height, &_nrChannels, 0);

	// Create a texture buffer and set up the parameters.
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (_localBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, _nrChannels == 4 ? GL_RGBA8 : GL_RGB, _width, _height, 0, _nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _localBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture");
	}

	stbi_image_free(_localBuffer);
}

Texture::~Texture()
{
	Unbind();
	glDeleteTextures(1, &_textureID);
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}