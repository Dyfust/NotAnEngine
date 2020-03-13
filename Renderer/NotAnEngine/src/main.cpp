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

using uint = unsigned int;
void Draw(const Mesh& mesh, Material& material, glm::mat4 modelMatrix);
void Draw(const MeshGroup&, Material& material, glm::mat4 modelMatrix);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// OpenGL setup stuff.
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
	Camera* cameraPtr = new Camera();
	DirectionalLight dirLight1 = DirectionalLight(glm::vec3(20, 0, -10), glm::vec3(0.35f, 0.25f, 0.65f));
	DirectionalLight dirLight2 = DirectionalLight(glm::vec3(-20, 0, -10), glm::vec3(0.5f, 0.0f, 0.0f));

	// Meshes.
	Mesh* sphere = Primitives::GenerateSphere(5.0, 100, 100);
	MeshGroup weapon;
	weapon.Load("Models\\SwordAndShield\\meshSwordShield.obj");

	// Uniform buffers.
	// Uniform buffer to hold uniforms assigned by the renderer.
	// Project View Matrix (mat4), Object Color (vec4), Directional Light (2 * vec4)
	UniformBuffer* uniformBuffer = new UniformBuffer(5, sizeof(glm::mat4) + 5 * sizeof(glm::vec4), GL_DYNAMIC_DRAW);

	// Shader.
	Shader phongShader = Shader("Shaders\\lit_vertex.glsl", "Shaders\\lit_frag.glsl");
	phongShader.BindUniformBlock("Engine", 5);

	// Textures.
	Texture swordAlbedoTexture = Texture("Textures\\SwordAndShield\\Sword_Albedo.png");
	Texture swordNormalTexture = Texture("Textures\\SwordAndShield\\Sword_Normal.png");

	Texture shieldAlbedoTexture = Texture("Textures\\SwordAndShield\\Shield_Albedo.png");
	Texture shieldNormalTexture = Texture("Textures\\SwordAndShield\\Shield_Normal.png");

	// Materials.
	float swordShininess = 0.25f;
	float swordSpecularReflectance = 0.25f;
	glm::vec4 swordColor(0.25f, 0.25f, 0.35f, 1.0f);
	Material swordMaterial = Material(phongShader);
	swordMaterial.AddTexture("albedo_map", &swordAlbedoTexture);
	swordMaterial.AddTexture("normal_map", &swordNormalTexture);
	swordMaterial.SetValue("object_color", GL_FLOAT_VEC4, (void*)&swordColor);
	swordMaterial.SetValue("shininess", GL_FLOAT, (void*)&swordShininess);
	swordMaterial.SetValue("specular_reflectance", GL_FLOAT, (void*)&swordSpecularReflectance);

	float shieldShininess = 1.0f;
	float shieldSpecularReflectance = 0.75f;
	glm::vec4 shieldColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Material shieldMaterial = Material(phongShader);
	shieldMaterial.AddTexture("albedo_map", &shieldAlbedoTexture);
	shieldMaterial.AddTexture("normal_map", &shieldNormalTexture);
	shieldMaterial.SetValue("object_color", GL_FLOAT_VEC4, (void*)&shieldColor);
	swordMaterial.SetValue("shininess", GL_FLOAT, (void*)&shieldShininess);
	swordMaterial.SetValue("specular_reflectance", GL_FLOAT, (void*)& shieldSpecularReflectance);
	// ---------------

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.35f, 0.35f, 0.35f, 1.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float deltatime = 1.0f / 60.0f;
		cameraPtr->Update(deltatime);

		glm::vec3 tmp = cameraPtr->GetPosition();
		glm::vec4 camera_pos = glm::vec4(tmp, 1.0f);
		glm::mat4 pvMatrix = cameraPtr->GetProjectionViewMatrix();

		uniformBuffer->UpdateBufferData(0, sizeof(glm::mat4), glm::value_ptr(pvMatrix));
		uniformBuffer->UpdateBufferData(sizeof(glm::mat4), sizeof(glm::vec4), glm::value_ptr(camera_pos));
		// First directional light.
		uniformBuffer->UpdateBufferData(sizeof(glm::mat4) + sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(dirLight1.position, 1.0f)));
		uniformBuffer->UpdateBufferData(sizeof(glm::mat4) + 2 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(dirLight1.color, 1.0f)));
		// Second directional light.
		uniformBuffer->UpdateBufferData(sizeof(glm::mat4) + 3 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(dirLight2.position, 1.0f)));
		uniformBuffer->UpdateBufferData(sizeof(glm::mat4) + 4 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(dirLight2.color, 1.0f)));

		glm::mat4 model = glm::mat4(1);
		model[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
		model = glm::rotate(model, 3.1415f / 2.0f, glm::vec3(0.0, 1.0, 0.0));

		Draw(weapon.GetMeshes().at(1), swordMaterial, model);
		Draw(weapon.GetMeshes().at(0), shieldMaterial, model);		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	delete cameraPtr;
	delete sphere;
	delete uniformBuffer;
	return 0;
}

void Draw(const Mesh& mesh, Material& material, glm::mat4 modelMatrix)
{
	material.SetValue("model_matrix", GL_FLOAT_MAT4, (void*)& modelMatrix);
	material.Bind();
	mesh.Bind();

	glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);

	material.Unbind();
	mesh.Unbind();
}

void Draw(const MeshGroup& group, Material& material, glm::mat4 modelMatrix)
{
	for (auto m : group.GetMeshes())
	{
		Draw(m, material, modelMatrix);
	}
}