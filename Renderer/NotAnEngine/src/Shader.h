#pragma once
#include "Uniform.h"
#include "ext.hpp"
#include "glm.hpp"
#include <string>
#include <vector>

class Shader
{
private:
	unsigned int _shaderProgramID;
	unsigned int _vertexID;
	unsigned int _fragmentID;

	char* _vertexSrc;
	char* _fragmentSrc;

	std::vector<Uniform> _uniforms;
	std::string _stringBuffer;

	void CreateShader(const char* vertexPath, const char* fragmentPath);
	void CompileShader(unsigned int ID);
	void LoadShaderFile(const char* path, char** srcBuffer);
	void CacheUniforms();
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader() = delete;
	~Shader();

	void SetUniformMatrix4fv(const char* name, glm::mat4& value);
	void SetUniform4fv(const char* name, glm::vec4& value);
	void SetUniform3fv(const char* name, glm::vec3& value);
	void SetUniform1f(const char* name, float& value);
	void SetUniform1i(const char* name, int value);

	void BindUniformBlock(const char* blockName, unsigned int bindingPoint);

	void Bind();
	void Unbind();

	const std::vector<Uniform>& GetUniforms();
};