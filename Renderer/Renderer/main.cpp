#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "fstream"
#include "sstream"
#include "camera.h"
#include "vertex.h"

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
	vertex verticies[num_verts]
	{
		// AWAY FACE
		vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1)),  // Away top left 0
		vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1)), // Away top right 1
		vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1)), // Away bottom left 2
		vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1)), // Away bottom rigt 3

		// TOWARDS FACE
		vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards top left 4
		vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards top right 5
		vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards bottom left 6
		vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards bottom right 7

		// LEFT FACE
		vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1, 0, 0)),  // Away top left 8
		vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1, 0, 0)), // Towards top left 9
		vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1, 0, 0)), // Away bottom left 10
		vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1, 0, 0)), // Towards bottom left 11

		// RIGHT FACE
		vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0)),  // Away top right 12
		vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 0, 0)), // Towards top right 13
		vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0)), // Away bottom right 14
		vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0)), // Towards bottom right 15

		// BOTTOM FACE
		vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0)), // Away bottom left 16
		vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0)), // Away bottom right 17
		vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0)), // Towards bottom left 18
		vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0)), // Towards bottom right 19

		// TOP FACE
		vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0)),  // Away top left 20
		vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0)),  // Away top right 21
		vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0)), // Towards top left 22
		vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0)) // Towards top right 23
	};
	// BACK, RIGHT BROKEN
	const int index_buffer_size = 36;
	int index_buffer[3 * index_buffer_size]
	{
		// AWAY
		1,2,0,
		3,2,1,

		// TOWARDS
		4,6,5,
		5,6,7,

		// LEFT
		8,10,9,
		9,10,11,

		// RIGHT
		13,14,12,
		15,14,13,

		// BOTTOM 
		17,18,16,
		19,18,17,

		// TOP
		20,22,21,
		21,22,23
	};


	// Vertex array object
	uint VAO;
	// Vertex buffer object
	uint VBO;
	uint IBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, num_verts * sizeof(vertex), verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size * sizeof(int), index_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(glm::vec3));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ---------------

	glm::mat4 model = glm::mat4(1.0f);

	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	
	camera* camera_ptr = new camera();

	// Load vertex shader.
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
		printf("Failed to load vertex shader\n");
	}

	// Load fragment shader
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
		printf("Failed to load fragment shader\n");
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
		printf("Failed to link shaders\n");
		GLint log_length = 0;
		glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);
		char* log = new char[log_length];
		glGetProgramInfoLog(shader_program_ID, log_length, 0, log);

		std::string log_message(log);
		printf(log_message.c_str());
		delete[] log;
		return -5;
	}

	//glPolygonMode(GL_BACK, GL_LINE);
	
	glDisable(GL_CULL_FACE);
	// Clear color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::rotate(model, 0.016f / 3.0f, glm::vec3(0, 1, 0));
		glm::vec3 light_source = glm::vec3(0, 0, 5);

		glUseProgram(shader_program_ID);
		auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(camera_ptr->get_projection_vew_matrix()));

		uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));

		uniform_location = glGetUniformLocation(shader_program_ID, "color");
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));

		uniform_location = glGetUniformLocation(shader_program_ID, "light_source");
		glUniform3fv(uniform_location, 1, glm::value_ptr(light_source));

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, num_verts);
		glDrawElements(GL_TRIANGLES, index_buffer_size, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}