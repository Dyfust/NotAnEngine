#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "fstream"
#include "sstream"
#include "camera.h"

using uint = unsigned int;
int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Renderer", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();

		return -3;
	}

	const int num_verts = 24;
	glm::vec3 verticies[num_verts]
	{
		glm::vec3(-0.5f, -0.5, 0.5f),
		glm::vec3(0.5f, -0.5, 0.5f),
		glm::vec3(-0.5f, -0.5, -0.5f),
		glm::vec3(0.5f, -0.5, 0.5f),
		glm::vec3(-0.5f, -0.5, -0.5f),
		glm::vec3(0.5f, -0.5, -0.5f),

		glm::vec3(-0.5f, 0.5, 0.5f),
		glm::vec3(0.5f, 0.5, 0.5f),
		glm::vec3(-0.5f, 0.5, -0.5f),
		glm::vec3(0.5f, 0.5, 0.5f),
		glm::vec3(-0.5f, 0.5, -0.5f),
		glm::vec3(0.5f, 0.5, -0.5f),

		glm::vec3(-0.5f, 0.5f, -0.5),
		glm::vec3(0.5f, 0.5f, -0.5),
		glm::vec3(-0.5f, -0.5f, -0.5),
		glm::vec3(0.5f, 0.5f, -0.5),
		glm::vec3(-0.5f, -0.5f, -0.5),
		glm::vec3(0.5f, -0.5f, -0.5),

		glm::vec3(-0.5f, 0.5f, 0.5),
		glm::vec3(0.5f, 0.5f, 0.5),
		glm::vec3(-0.5f, -0.5f, 0.5),
		glm::vec3(0.5f, 0.5f, 0.5),
		glm::vec3(-0.5f, -0.5f, 0.5),
		glm::vec3(0.5f, -0.5f, 0.5)
	};


	glm::mat4 model = glm::mat4(1.0f);

	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	
	camera* camera_ptr = new camera();


	// Load mesh.
	uint VAO;
	uint VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, num_verts * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Load shaders.
	uint vertex_shader_ID;
	uint fragment_shader_ID;

	std::string shader_data;
	GLint success = GL_FALSE;

	const char* data;

	std::ifstream vert_file_stream("..\\Shaders\\simple_vertex.glsl", std::ifstream::in);
	std::stringstream vertex_string_stream;

	if (vert_file_stream.is_open())
	{
		vertex_string_stream << vert_file_stream.rdbuf();
		shader_data = vertex_string_stream.str();
		vert_file_stream.close();
	}

	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	data = shader_data.c_str();

	glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data, 0);
	glCompileShader(vertex_shader_ID);

	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		return -4;
	}

	std::ifstream frag_file_stream("..\\Shaders\\simple_frag.glsl", std::ifstream::in);
	std::stringstream fragment_string_stream;
	if (frag_file_stream.is_open())
	{
		fragment_string_stream << frag_file_stream.rdbuf();
		shader_data = fragment_string_stream.str();
		frag_file_stream.close();
	}

	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	data = shader_data.c_str();

	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data, 0);
	glCompileShader(fragment_shader_ID);

	success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		return -4;
	}
	
	// Shader program
	uint shader_program_ID = glCreateProgram();

	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	glLinkProgram(shader_program_ID);

	success = GL_FALSE;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint log_length = 0;
		glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);
		char* log = new char[log_length];
		glGetProgramInfoLog(shader_program_ID, log_length, 0, log);

		std::string log_message(log);
		printf(log_message.c_str());
		delete[] log;
		return -5;
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Clear color.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::rotate(model, 0.016f, glm::vec3(0.707f, 0.707f, 0));

		glUseProgram(shader_program_ID);
		auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(camera_ptr->get_projection_vew_matrix()));

		uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));

		uniform_location = glGetUniformLocation(shader_program_ID, "color");
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, num_verts);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}