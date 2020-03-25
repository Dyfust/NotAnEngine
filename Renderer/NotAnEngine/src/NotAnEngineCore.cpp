#include "NotAnEngineCore.h"
#include "Renderer.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Primitives.h"
#include <iostream>

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

		OnUpdate(1.0 / 60.0f);
		glfwPollEvents();
		_window->Update();
	}

	OnShutdown();
	Terminate();
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
	_quad = Primitives::GenerateQuad();
	
	_shader2D = new Shader("working\\Shaders\\2d_vertex.glsl", "working\\Shaders\\2d_frag.glsl");
	_shader2D->BindUniformBlock("Engine", 5);

	_spriteTexture = new Texture("working\\Textures\\Ninja.png");
	glm::vec4 spriteColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

	_spriteMaterial = new Material(*_shader2D);
	_spriteMaterial->SetValue("color", GL_FLOAT_VEC4, (void*)& spriteColor);
	_spriteMaterial->AddTexture("albedo_map", _spriteTexture);
}

void NotAnEngineCore::OnUpdate(float deltaTime)
{
	_mainCamera->Update(deltaTime);

	_renderer->Render(*_quad, *_spriteMaterial, glm::mat4(1));
}

void NotAnEngineCore::OnShutdown()
{
	delete _spriteMaterial;
	delete _spriteTexture;
	delete _shader2D;
}

void NotAnEngineCore::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
