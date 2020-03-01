#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include "camera.h"
#include "vertex.h"
#include "Shader.h"
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "OBJMesh.h"
#include "Texture.h"
#include "MeshGroup.h"
#include "Primitives.h"

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
	glm::vec3 lightSource = glm::vec3(20, 20, 50);
	glm::vec3 light_color = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 object_color = glm::vec3(75.0f / 255.0f, 92.0f / 255.0f, 245.0f / 255.0f);

	// Mesh
	MeshGroup house;
	house.Load("../Models/MayanHouse/SM_MayanHouse_01.obj");

	MeshGroup bunny;
	bunny.Load("../Models/Dragon.obj");

	Mesh* sphere = Primitives::GenerateSphere(5.0, 100, 100);

	// Shader
	Shader basicShader = Shader("..\\Shaders\\lit_vertex.glsl", "..\\Shaders\\lit_frag.glsl");
	basicShader.Bind();
	basicShader.SetUniform3fv("light_source", lightSource);
	basicShader.SetUniform3fv("light_color", light_color);
	basicShader.SetUniform3fv("color", object_color);
	
	// ---------------

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.35f, 0.35f, 0.35f, 1.0f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	float time = 0.0f;

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		float deltatime = 1.0f / 60.0f;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera_ptr->update(0.016f);

		glm::mat4 model = glm::mat4(1);
		glm::mat4 pvMatrix = camera_ptr->get_projection_vew_matrix();
		basicShader.SetUniformMatrix4fv("projection_view_matrix", pvMatrix);
		basicShader.SetUniformMatrix4fv("model_matrix", model);

		glm::vec3 camera_pos = camera_ptr->get_position();
		basicShader.SetUniform3fv("view_point", camera_pos);

		bunny.Draw();

		model[3] = glm::vec4(15.0, 0.0f, 0.0f, 1.0f);
		basicShader.SetUniformMatrix4fv("model_matrix", model);
		sphere->Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		time += deltatime;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}