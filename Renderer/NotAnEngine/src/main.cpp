#include "Renderer.h"
#include "camera.h"
#include "vertex.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "MeshGroup.h"
#include "Primitives.h"
#include "Lights.h"
#include "Material.h"
#include "UniformBuffer.h"
#include <string>
#include <iostream>

using uint = unsigned int;
void Draw(const Mesh& mesh, Texture& albedo, Texture& normal);
void Draw(const MeshGroup&, Texture& albedo, Texture& normal);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
	DirectionalLight dirLight = DirectionalLight(glm::vec3(25, 10, 20), glm::vec3(1.0, 1.0, 1.0));
	glm::vec3 object_color = glm::vec3(1.0, 0.5, 1.0);

	// Meshes
	Mesh* sphere = Primitives::GenerateSphere(5.0, 100, 100);

	MeshGroup weapon;
	weapon.Load("Models\\SwordAndShield\\meshSwordShield.obj");

	// Shader
	Shader phongShader = Shader("Shaders\\lit_vertex.glsl", "Shaders\\lit_frag.glsl");
	phongShader.Bind();
	phongShader.SetUniform3fv("directonal_light.source", dirLight.position);
	phongShader.SetUniform3fv("directional_light.color", dirLight.color);
	phongShader.SetUniform3fv("color", object_color);

	UniformBuffer stuff = UniformBuffer(sizeof(glm::mat4) + sizeof(glm::vec3), 5, GL_DYNAMIC_DRAW);
	phongShader.BindUniformBlock("Engine", 5);

	Material* material = new Material(phongShader);

	// Textures
	Texture swordTex = Texture("Textures\\SwordAndShield\\Sword_Albedo.png", 0);
	Texture swordNormal = Texture("Textures\\SwordAndShield\\Sword_Normal.png", 1);

	Texture shieldTex = Texture("Textures\\SwordAndShield\\Shield_Albedo.png", 2);
	Texture shieldNormal = Texture("Textures\\SwordAndShield\\Shield_Normal.png", 3);
	
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float deltatime = 1.0f / 60.0f;

		camera_ptr->update(0.016f);

		glm::vec3 camera_pos = camera_ptr->get_position();
		glm::mat4 pvMatrix = camera_ptr->get_projection_vew_matrix();
		stuff.UpdateBuffer(0, sizeof(glm::mat4), glm::value_ptr(pvMatrix));
		stuff.UpdateBuffer(sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(camera_pos));

		glm::mat4 model = glm::mat4(1);
		model[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
		model = glm::rotate(model, 3.1415f / 2.0f, glm::vec3(0.0, 1.0, 0.0));

		phongShader.SetUniformMatrix4fv("model_matrix", model);

		phongShader.SetUniform1i("albedo_map", 2);
		phongShader.SetUniform1i("normal_map", 3);
		Draw(weapon.GetMeshes().at(0), shieldTex, shieldNormal);

		phongShader.SetUniform1i("albedo_map", 0);
		phongShader.SetUniform1i("normal_map", 1);
		Draw(weapon.GetMeshes().at(1), swordTex, swordNormal);

		

		glfwSwapBuffers(window);
		glfwPollEvents();

		time += deltatime;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	delete camera_ptr;
	delete sphere;
	return 0;
}

void Draw(const Mesh& mesh, Texture& albedo, Texture& normal)
{
	albedo.Bind();
	normal.Bind();
	mesh.Bind();

	glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);

	mesh.Unbind();
	albedo.Unbind();
	normal.Bind();
}

void Draw(const MeshGroup& group, Texture& albedo, Texture& normal)
{
	for (auto m : group.GetMeshes())
	{
		Draw(m, albedo, normal);
	}
}
