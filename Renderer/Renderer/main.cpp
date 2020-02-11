#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "camera.h"
#include "vertex.h"
#include "Shader.h"
#include "Mesh.h"

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

	// ---------------

	camera* camera_ptr = new camera();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, 3.14f / 4, glm::vec3(0, 1, 0));
	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 lightSource = glm::vec3(0, 0, 5);


	Mesh* cube = new Mesh({
		// AWAY FACE
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1)),  // Away top left 0
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 0, -1)), // Away top right 1
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1)), // Away bottom left 2
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1)), // Away bottom rigt 3

		// TOWARDS FACE
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards top left 4
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards top right 5
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards bottom left 6
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, 0, 1)), // Towards bottom right 7

		// LEFT FACE
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1, 0, 0)),  // Away top left 8
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1, 0, 0)), // Towards top left 9
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1, 0, 0)), // Away bottom left 10
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1, 0, 0)), // Towards bottom left 11

		// RIGHT FACE
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1, 0, 0)),  // Away top right 12
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 0, 0)), // Towards top right 13
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1, 0, 0)), // Away bottom right 14
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1, 0, 0)), // Towards bottom right 15

		// BOTTOM FACE
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0)), // Away bottom left 16
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0, -1, 0)), // Away bottom right 17
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0)), // Towards bottom left 18
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0, -1, 0)), // Towards bottom right 19

		// TOP FACE
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0)),  // Away top left 20
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0, 1, 0)),  // Away top right 21
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0)), // Towards top left 22
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0, 1, 0)) // Towards top right 23
		},
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
		}
		);

	cube->Bind();

	// Shader
	Shader basicShader = Shader("..\\Shaders\\simple_vertex.glsl", "..\\Shaders\\simple_frag.glsl");
	basicShader.Bind();
	basicShader.SetUniform3fv("light_source", lightSource);
	basicShader.SetUniform4fv("color", color);
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model = glm::rotate(model, 0.016f / 3.0f, glm::vec3(0.707, 0.707, 0));

		camera_ptr->update(0.016f);

		glm::mat4 pvMatrix = camera_ptr->get_projection_vew_matrix();

		basicShader.SetUniformMatrix4fv("projection_view_matrix", pvMatrix);
		basicShader.SetUniformMatrix4fv("model_matrix", model);

		glDrawElements(GL_TRIANGLES, cube->GetIndicesCount(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}