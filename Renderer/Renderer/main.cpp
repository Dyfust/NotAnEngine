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
	glm::vec4 color = glm::vec4(196.0 / 255.0, 176.0 / 255.0, 228.0 / 255.0, 1.0);
	glm::vec3 lightSource = glm::vec3(300, 1000, 300);

	// Mesh
	aie::OBJMesh house = aie::OBJMesh();
	house.load("../Models/MayanHouse/SM_MayanHouse_01.obj");

	aie::OBJMesh sun = aie::OBJMesh();
	sun.load("../Models/Bunny.obj");

	// Shader
	Shader basicShader = Shader("..\\Shaders\\lit_vertex.glsl", "..\\Shaders\\lit_frag.glsl");
	basicShader.Bind();
	basicShader.SetUniform3fv("light_source", lightSource);
	basicShader.SetUniform4fv("color", color);

	// Texture
	Texture house_atlas = Texture("../Textures/MayanHouseTextures/T_Atlas_Albedo.tga", 0);
	Texture house_trim = Texture("../Textures/MayanHouseTextures/T_Trim_Albedo.tga", 1);

	basicShader.SetUniform1i("u_AtlasTexture", 0);
	basicShader.SetUniform1i("u_TrimTexture", 1);
	
	// ---------------

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	float time = 0.0f;

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		float deltatime = 1.0f / 60.0f;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::mat4(1);
		camera_ptr->update(0.016f);

		glm::mat4 pvMatrix = camera_ptr->get_projection_vew_matrix();

		basicShader.SetUniformMatrix4fv("projection_view_matrix", pvMatrix);

		house_atlas.Bind();
		house_trim.Bind();
		basicShader.SetUniformMatrix4fv("model_matrix", model);
		house.draw();

		house_atlas.Unbind();
		house_trim.Unbind();
		//model[3] = glm::vec4(glm::vec3(300, 50, 300), 1.0f);
		//basicShader.SetUniformMatrix4fv("model_matrix", model);
		//sun.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		time += deltatime;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}