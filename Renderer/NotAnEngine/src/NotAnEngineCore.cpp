#include "NotAnEngineCore.h"
#include "Renderer.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Primitives.h"
#include "MeshGroup.h"
#include "Events/EventDispatcher.h"
#include "Events/MousePressEvent.h"
#include "Events/MouseReleaseEvent.h"
#include <iostream>
#include <functional>

NotAnEngineCore::NotAnEngineCore(const char* title, unsigned int width, unsigned int height)
{
	_hasTerminated = false;

	// OpenGL setup stuff.
	if (!glfwInit())
	{
		std::cout << "GLFW failed to initialise!" << std::endl;
		return;
	}

	_window = new Window(width, height, title);
	_window->MakeContextCurrent();
	//_window->SetOnEventCallback(std::bind(&NotAnEngineCore::OnEvent, this, std::placeholders::_1));

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		std::cout << "Failed to load OpenGL functions!" << std::endl;
		glfwTerminate();
		return;
	}

	_renderer = new Renderer();
	_mainCamera = new Camera();
	_renderer->SetCamera(_mainCamera);
}

NotAnEngineCore::~NotAnEngineCore()
{
	if (!_hasTerminated)
		Terminate();
}

void NotAnEngineCore::Run()
{
	glfwSetInputMode(_window->GetWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(_window->GetWindowPtr(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	SetClearColor(0.35f, 0.35f, 0.35f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	OnStart();
	while (!glfwWindowShouldClose(_window->GetWindowPtr()) && glfwGetKey(_window->GetWindowPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OnUpdate(1.0f / 60.0f);
		glfwPollEvents();
		_window->Update();
	}

	OnShutdown();
	Terminate();
}

void NotAnEngineCore::OnEvent(Event& event)
{
	if (event.GetEventType() == Event::EventType::MousePressEvent) 
	{
		std::cout << "Mouse Button Pressed" << std::endl;
	}
	else if (event.GetEventType() == Event::EventType::MouseReleaseEvent)
	{
		std::cout << "Mouse Button Released" << std::endl;
	}
}

void NotAnEngineCore::Terminate()
{
	delete _renderer;
	delete _mainCamera;
	delete _window;

	glfwTerminate();
	_hasTerminated = true;
}

void NotAnEngineCore::OnStart()
{	
	_shader2D = new Shader("working\\Shaders\\2d_vertex.glsl", "working\\Shaders\\2d_frag.glsl");
	_shader2D->BindUniformBlock("Engine", 5);

	_spriteTexture = new Texture("working\\Textures\\Ninja.png");
	glm::vec4 spriteColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

	_spriteMaterial = new Material(*_shader2D);
	_spriteMaterial->SetValue("color", GL_FLOAT_VEC4, (void*)&spriteColor);
	_spriteMaterial->AddTexture("albedo_map", _spriteTexture);

	_shaderPhong = new Shader("working\\Shaders\\lit_vertex.glsl", "working\\Shaders\\lit_frag.glsl");
	_shaderPhong->BindUniformBlock("Engine", 5);

	_swordShield = new MeshGroup();
	_swordShield->Load("working\\Models\\SwordAndShield\\meshSwordShield.obj");
	
	_swordAlbedo = new Texture("working\\Textures\\SwordAndShield\\Sword_Albedo.png");
	_swordNormal = new Texture("working\\Textures\\SwordAndShield\\Sword_Normal.png");

	_shieldAlbedo = new Texture("working\\Textures\\SwordAndShield\\Shield_Albedo.png");
	_shieldNormal = new Texture("working\\Textures\\SwordAndShield\\Shield_Normal.png");

	_swordMaterial = new Material(*_shaderPhong);
	_swordMaterial->AddTexture("albedo_map", _swordAlbedo);
	_swordMaterial->AddTexture("normal_map", _swordNormal);
	_swordMaterial->SetValue("object_color", GL_FLOAT_VEC4, (void*)&_swordColor);
	_swordMaterial->SetValue("shininess", GL_FLOAT, (void*)&_swordShininess);
	_swordMaterial->SetValue("specular_reflectance", GL_FLOAT, (void*)&_swordReflectance);

	_shieldMaterial = new Material(*_shaderPhong);
	_shieldMaterial->AddTexture("albedo_map", _shieldAlbedo);
	_shieldMaterial->AddTexture("normal_map", _shieldNormal);
	_shieldMaterial->SetValue("object_color", GL_FLOAT_VEC4, (void*)& _shieldColor);
	_shieldMaterial->SetValue("shininess", GL_FLOAT, (void*)& _shieldShininess);
	_shieldMaterial->SetValue("specular_reflectance", GL_FLOAT, (void*)& _shieldReflectance);

	_model = glm::rotate(_model, -3.14159265359f / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	_sun = Primitives::GenerateSphere(1.0f, 20, 20);
	_sunAlbedo = new Texture("working\\Textures\\Sun.jpg");
	_sunMaterial = new Material(*_shader2D);
	_sunMaterial->AddTexture("albedo_map", _sunAlbedo);
}

void NotAnEngineCore::OnUpdate(float deltaTime)
{
	_mainCamera->Update(deltaTime);

	_renderer->Render(*_sun, *_sunMaterial, glm::mat4(1));
	_renderer->Render(*_swordShield->GetMeshes().at(1), *_swordMaterial, _model);
	_renderer->Render(*_swordShield->GetMeshes().at(0), *_shieldMaterial, _model);
}

void NotAnEngineCore::OnFixedUpdate(float timeStep)
{

}

void NotAnEngineCore::OnShutdown()
{
	//delete _spriteMaterial;
	//delete _spriteTexture;
	delete _shader2D;
}

void NotAnEngineCore::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
