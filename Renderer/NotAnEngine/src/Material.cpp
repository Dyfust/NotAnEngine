#include "Material.h"

Material::Material(Shader& shader)
{
	_shader = &shader;
	_textureCount = 0;
}

void Material::SetUniform(const char* name, GLenum type, void* data)
{
	switch (type)
	{
	case GL_FLOAT_MAT4:
		_shader->SetUniformMatrix4fv(name, *(glm::mat4*)data);
		break;
	case GL_FLOAT_VEC4:
		_shader->SetUniform4fv(name, *(glm::vec4*)data);
		break;
	case GL_FLOAT_VEC3:
		_shader->SetUniform3fv(name, *(glm::vec3*)data);
		break;
	case GL_FLOAT:
		_shader->SetUniform1f(name, *(float*)data);
		break;
	case GL_INT:
		_shader->SetUniform1i(name, *(int*)data);
		break;
	}
}

void Material::SetValue(const char* name, GLenum type, void* data)
{
	if (_uniforms.count(name) > 0)
	{
		auto iterator = _uniforms.find(name);
		iterator->second._value = data;
		return;
	}

	Uniform uniform = Uniform(name, type, data);
	_uniforms.insert({ name, uniform });
}

void Material::AddTexture(const char* name, Texture* texture)
{
	TextureUniform t = TextureUniform(name, texture);
	_textures.push_back(t);
}

void Material::Bind()
{
	_shader->Bind();

	for (int i = 0; i < _textures.size(); i++)
	{
		_textures[i]._texture->Bind(_textureCount);
		SetUniform(_textures[i]._name, GL_INT, (void*)&_textureCount);
		_textureCount++;
	}

	for (auto u : _uniforms)
	{
		SetUniform(u.second._name, u.second._type, u.second._value);
	}
}

void Material::Unbind()
{
	_shader->Unbind();

	for (int i = 0; i < _textures.size(); i++)
	{
		_textures[i]._texture->Unbind();
	}

	_textureCount = 0;
}