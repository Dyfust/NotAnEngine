#pragma once
#include <string>
#include "ext.hpp";
#include "glm.hpp";

class Shader
{
private:
	unsigned int _shaderID;
	unsigned int _vertexID;
	unsigned int _fragmentID;

	char* _vertexSrc;
	char* _fragmentSrc;

	void CreateShader(char* vertexPath, char* fragmentPath);
	void ParseShaderFile(char* path, char* srcBuffer) const;
public:
	Shader(char* vertexPath, char* fragmentPath);
	~Shader();

	void SetUniformMatrix4fv(char* name, glm::mat4& value);
	void SetUniform4fv(char* name, glm::vec4& value);
	void SetUniform3fv(char* name, glm::vec3& value);

	void Bind();
	void Unbind();
};

