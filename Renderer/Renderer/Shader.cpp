#include "Shader.h"
#include "Renderer.h"
#include "fstream"
#include "sstream"
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	CreateShader(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	Unbind();
	glDeleteProgram(_shaderProgramID);
	glDeleteShader(_vertexID);
	glDeleteShader(_fragmentID);
}

void Shader::CreateShader(const char* vertexPath, const char* fragmentPath)
{
	// Create shaders.
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	// Load glsl code into shaders.
	LoadShaderFile(vertexPath, &_vertexSrc);
	glShaderSource(_vertexID, 1, (const GLchar**)&_vertexSrc, 0);

	LoadShaderFile(fragmentPath, &_fragmentSrc);
	glShaderSource(_fragmentID, 1, (const GLchar**)&_fragmentSrc, 0);

	// Compile shaders.
	CompileShader(_vertexID);
	CompileShader(_fragmentID);

	// Init shader program w/ vert & frag shaders.
	_shaderProgramID = glCreateProgram();
	glAttachShader(_shaderProgramID, _vertexID);
	glAttachShader(_shaderProgramID, _fragmentID);

	// Link shader program.
	glLinkProgram(_shaderProgramID);

	GLint status = GL_FALSE;
	glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		printf("Failed to link shader\n");
		GLint logLength = 0;
		glGetProgramiv(_shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		char* output = new char[logLength];
		glGetProgramInfoLog(_shaderProgramID, logLength, 0, output);

		printf(output);
		delete[] output;
	}

	LoadUniforms();
}

void Shader::CompileShader(unsigned int shaderID)
{
	GLint status = GL_FALSE;
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if (status == false)
	{
		std::cout << "Failed to load shader: " << shaderID << std::endl;
	}
}

void Shader::LoadShaderFile(const char* path, char** srcBuffer)
{
	std::ifstream fileStream(path, std::ifstream::in);
	_stringBuffer.clear();

	if (fileStream.is_open())
	{
		std::stringstream stringStream; 
		stringStream << fileStream.rdbuf();
		_stringBuffer = stringStream.str();
		fileStream.close();
	}

	*srcBuffer = (char*)_stringBuffer.c_str();
}

void Shader::LoadUniforms()
{
	int count;
	glGetProgramiv(_shaderProgramID, GL_ACTIVE_UNIFORMS, &count);

	char tmpName[Uniform::nameBufferSize];
	int tmpSize;
	int tmpLength;
	GLenum tmpType;

	Uniform tmpUniform;

	for (size_t i = 0; i < count; i++)
	{	
		glGetActiveUniform(_shaderProgramID, i, Uniform::nameBufferSize, &tmpLength, &tmpSize, &tmpType, tmpName);
		strcpy_s(tmpUniform._name, tmpName);
		tmpUniform._type = tmpType;
		_uniforms.push_back(tmpUniform);
	}

	for (auto u : _uniforms)
	{
		char buffer[32]{ 0 };
		sprintf_s(buffer, "%X", u._type);
		std::string name = u._name;
		std::cout << name << ", " << buffer << std::endl;
	}
}

void Shader::SetUniformMatrix4fv(const char* name, glm::mat4& value)
{
	int uniformLocation = glGetUniformLocation(_shaderProgramID, name);
	glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void Shader::SetUniform4fv(const char* name, glm::vec4& value)
{
	int uniformLocation = glGetUniformLocation(_shaderProgramID, name);
	glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetUniform3fv(const char* name, glm::vec3& value)
{
	int uniformLocation = glGetUniformLocation(_shaderProgramID, name);
	glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetUniform1f(const char* name, float& value)
{
	int uniformLocation = glGetUniformLocation(_shaderProgramID, name);
	glUniform1f(uniformLocation, value);
}

void Shader::SetUniform1i(const char* name, int value)
{
	int uniformLocation = glGetUniformLocation(_shaderProgramID, name);
	glUniform1i(uniformLocation, value);
}

void Shader::Bind()
{
	glUseProgram(_shaderProgramID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

const std::vector<Uniform>& Shader::GetUniforms()
{
	return _uniforms;
}