#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include <vector>
#include <unordered_map>
#pragma once

class Material
{
public:
	Material(Shader& shader);
	Material() = delete;

	// Cache these uniform values in the material and only upload them to the shader when this material is bound.
	void SetValue(const char* name, GLenum type, void* data);
	void AddTexture(const char* name, Texture* texture);

	void Bind();
	void Unbind();
private:
	class TextureUniform
	{
	public:
		const char* _name;
		Texture* _texture;

		TextureUniform(const char* name, Texture* texture) : _name(name), _texture(texture)
		{}
	};

	Shader* _shader;
	std::unordered_map<const char* ,Uniform> _uniforms;

	unsigned int _textureCount;
	std::vector<TextureUniform> _textures;

	void SetUniform(const char* name, GLenum type, void* data);
};