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

	Renderer renderer;
	// ---------------
	Camera* cameraPtr = new Camera();
	renderer.SetCamera(cameraPtr);

	// Meshes.
	//Mesh* sphere = Primitives::GenerateSphere(5.0, 100, 100);
	//MeshGroup weapon;
	//weapon.Load("working\\Models\\SwordAndShield\\meshSwordShield.obj");

	// Shaders.
	//Shader phongShader = Shader("working\\Shaders\\lit_vertex.glsl", "working\\Shaders\\lit_frag.glsl");
	//phongShader.BindUniformBlock("Engine", 5);

	// Textures.
	//Texture swordAlbedoTexture = Texture("working\\Textures\\SwordAndShield\\Sword_Albedo.png");
	//Texture swordNormalTexture = Texture("working\\Textures\\SwordAndShield\\Sword_Normal.png");
	//Texture shieldAlbedoTexture = Texture("working\\Textures\\SwordAndShield\\Shield_Albedo.png");
	//Texture shieldNormalTexture = Texture("working\\Textures\\SwordAndShield\\Shield_Normal.png");

	// Materials.
	//float swordShininess = 0.25f;
	//float swordSpecularReflectance = 0.25f;
	//glm::vec4 swordColor(0.25f, 0.25f, 0.35f, 1.0f);
	//Material swordMaterial = Material(phongShader);
	//swordMaterial.AddTexture("albedo_map", &swordAlbedoTexture);
	//swordMaterial.AddTexture("normal_map", &swordNormalTexture);
	//swordMaterial.SetValue("object_color", GL_FLOAT_VEC4, (void*)&swordColor);
	//swordMaterial.SetValue("shininess", GL_FLOAT, (void*)&swordShininess);
	//swordMaterial.SetValue("specular_reflectance", GL_FLOAT, (void*)&swordSpecularReflectance);

	//float shieldShininess = 1.0f;
	//float shieldSpecularReflectance = 0.75f;
	//glm::vec4 shieldColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	//Material shieldMaterial = Material(phongShader);
	//shieldMaterial.AddTexture("albedo_map", &shieldAlbedoTexture);
	//shieldMaterial.AddTexture("normal_map", &shieldNormalTexture);
	//shieldMaterial.SetValue("object_color", GL_FLOAT_VEC4, (void*)&shieldColor);
	//swordMaterial.SetValue("shininess", GL_FLOAT, (void*)&shieldShininess);
	//swordMaterial.SetValue("specular_reflectance", GL_FLOAT, (void*)& shieldSpecularReflectance);

	Mesh* quad = Primitives::GenerateQuad();

	Shader shader2D = Shader("working\\Shaders\\2d_vertex.glsl", "working\\Shaders\\2d_frag.glsl");
	shader2D.BindUniformBlock("Engine", 5);
	Material spriteMaterial = Material(shader2D);

	glm::vec4 spriteColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	spriteMaterial.SetValue("color", GL_FLOAT_VEC4, (void*)&spriteColor);

	Texture ninjaSprite = Texture("working\\Textures\\Ninja.png");
	spriteMaterial.AddTexture("albedo_map", &ninjaSprite);
	// ---------------

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

		glm::mat4 model = glm::mat4(1);
		model[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
		model = glm::scale(model, glm::vec3(4.0, 4.0, 1.0));

		renderer.Render(*quad, spriteMaterial, model);
		//renderer.Render(weapon.GetMeshes().at(0), shieldMaterial, model);		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	delete cameraPtr;
	//delete sphere;
	//delete uniformBuffer;
	return 0;
}