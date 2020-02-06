#include "Shader.h"
#include "Renderer.h"
#include "fstream"
#include "sstream"

Shader::Shader(char* vertexPath, char* fragmentPath)
{
	CreateShader(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(_shaderID);
	glDeleteShader(_vertexID);
	glDeleteShader(_fragmentID);
}

void Shader::CreateShader(char* vertexPath, char* fragmentPath)
{
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	ParseShaderFile(vertexPath, _vertexSrc);
	ParseShaderFile(fragmentPath, _fragmentSrc);

	glShaderSource(_vertexID, 1, (const GLchar * *)_vertexSrc, 0);
	glShaderSource(_fragmentID, 1, (const GLchar * *)_fragmentSrc, 0);

	glCompileShader(_vertexID);
	glCompileShader(_fragmentID);

	_shaderID = glCreateProgram();
	glAttachShader(_shaderID, _vertexID);
	glAttachShader(_shaderID, _fragmentID);

	glLinkProgram(_shaderID);
}

void Shader::ParseShaderFile(char* path, char* srcBuffer) const
{
	std::ifstream fileStream("path", std::ifstream::in);

	if (fileStream.is_open())
	{
		fileStream.seekg(0, fileStream.end);
		int count = fileStream.tellg();
		fileStream.seekg(0, fileStream.beg);

		fileStream.read(srcBuffer, count);
		fileStream.close();
	}
}

void Shader::SetUniformMatrix4fv(char* name, glm::mat4& value)
{
	int uniformLocation = glGetUniformLocation(_shaderID, name);
	glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void Shader::SetUniform4fv(char* name, glm::vec4& value)
{
	int uniformLocation = glGetUniformLocation(_shaderID, name);
	glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetUniform3fv(char* name, glm::vec3& value)
{
	int uniformLocation = glGetUniformLocation(_shaderID, name);
	glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::Bind()
{
	glUseProgram(_shaderID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

// "..\\Shaders\\simple_vertex.glsl"