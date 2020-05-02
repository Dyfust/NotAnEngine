#include "NotAnEngineCore.h"
#include "Renderer.h"
#include "Window.h"
#include "Camera.h"
#include "Events/EventDispatcher.h"
#include "Events/MousePressEvent.h"
#include "Events/MouseReleaseEvent.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Primitives.h"
#include "MeshGroup.h"
#include "Entity.h"
#include "Physics/PhysicsEngine.h"
#include "Physics/2D/PhysicsBody2D.h"
#include "Physics/2D/RigidBody2D.h"
#include "Physics/2D/Collider2D.h"
#include "Physics/2D/AABB.h"
#include "Physics/2D/Circle.h"
#include "Physics/2D/Line.h"

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
	_window->SetOnEventCallback(std::bind(&NotAnEngineCore::OnEvent, this, std::placeholders::_1));

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
	_physicsEngine = new PhysicsEngine(glm::vec2(0.0f, -10.0f), 0.016f);

	_circleEntity = new Entity();
	_circleEntity2 = new Entity();
	_squareEntity = new Entity();
	_squareEntity2 = new Entity();

	Entity* _bottomLineEntity = new Entity();
	Entity* _topLineEntity = new Entity();
	Entity* _leftLineEntity = new Entity();
	Entity* _rightLineEntity = new Entity();
	
	Collider2D* bottomLineCollider = new Line(glm::vec2(0.0f, 1.0f), -10.0f);
	Collider2D* topLineCollider = new Line(glm::vec2(0.0f, -1.0f), -10.0f);
	Collider2D* leftLineCollider = new Line(glm::vec2(1.0f, 0.0f), -17.5f);
	Collider2D* rightLineCollider = new Line(glm::vec2(-1.0f, 0.0f), -18.0f);

	Collider2D* circleEntityCollider = new Circle(2.0f);
	Collider2D* circleEntityCollider2 = new Circle(4.0f);
	Collider2D* squareEntityCollider = new AABB(glm::vec2(4.0f));
	Collider2D* squareEntityCollider2 = new AABB(glm::vec2(2.0f));

	PhysicsBody2D* bottomLineBody = new PhysicsBody2D(_bottomLineEntity, bottomLineCollider);
	PhysicsBody2D* topLineBody = new PhysicsBody2D(_topLineEntity, topLineCollider);
	PhysicsBody2D* leftLineBody = new PhysicsBody2D(_leftLineEntity, leftLineCollider);
	PhysicsBody2D* rightLineBody = new PhysicsBody2D(_rightLineEntity, rightLineCollider);

	RigidBody2D* circleEntityRigidBody = new RigidBody2D(_circleEntity, circleEntityCollider, 1.0f, 1.0f);;
	RigidBody2D* circleEntityRigidBody2 = new RigidBody2D(_circleEntity2, circleEntityCollider2, 3.0f, 1.0f);;

	RigidBody2D* squareEntityRigidBody = new RigidBody2D(_squareEntity, squareEntityCollider, 3.0f, 0.5f);;
	RigidBody2D* squareEntityRigidBody2 = new RigidBody2D(_squareEntity2, squareEntityCollider2, 1.0f, 0.5f);;

	_circleEntity->SetPhysicsBody(circleEntityRigidBody);
	_circleEntity2->SetPhysicsBody(circleEntityRigidBody2);

	_circleEntity->Translate(glm::vec3(20.0f, 0.0f, 0.0f));
	_squareEntity->Translate(glm::vec3(15.0f, 0.0f, 0.0f));
	_squareEntity2->Translate(glm::vec3(-10.0f, 0.0f, 0.0f));

	_squareEntity->SetPhysicsBody(squareEntityRigidBody);
	_squareEntity2->SetPhysicsBody(squareEntityRigidBody2);


	_physicsEngine->AddPhysicsBody2D(bottomLineBody);
	_physicsEngine->AddPhysicsBody2D(topLineBody);
	_physicsEngine->AddPhysicsBody2D(leftLineBody);
	_physicsEngine->AddPhysicsBody2D(rightLineBody);
	_physicsEngine->AddPhysicsBody2D(&_circleEntity->GetPhysicsBody());
	_physicsEngine->AddPhysicsBody2D(&_circleEntity2->GetPhysicsBody());
	_physicsEngine->AddPhysicsBody2D(&_squareEntity->GetPhysicsBody());
	_physicsEngine->AddPhysicsBody2D(&_squareEntity2->GetPhysicsBody());

	circleEntityRigidBody->AddForce(glm::vec2(-20.0f, 0.0f));
}

void NotAnEngineCore::OnUpdate(float deltaTime)
{
	_physicsEngine->Update(deltaTime);
	_mainCamera->Update(deltaTime);

	glPolygonMode(GL_FRONT, GL_LINE);
	_renderer->RenderCircle(_circleEntity->GetWorldMatrix()[3], 2.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	_renderer->RenderCircle(_circleEntity2->GetWorldMatrix()[3], 4.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	_renderer->RenderQuad(_squareEntity->GetWorldMatrix()[3], glm::vec2(4.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	_renderer->RenderQuad(_squareEntity2->GetWorldMatrix()[3], glm::vec2(2.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void NotAnEngineCore::OnFixedUpdate(float timeStep)
{

}

void NotAnEngineCore::OnShutdown()
{

}

void NotAnEngineCore::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
