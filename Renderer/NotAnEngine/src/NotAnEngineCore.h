#pragma once
#include "glm.hpp"
#include "Events/Event.h"
#include "Events/MouseMovedEvent.h"

class Window;
class Renderer;
class Camera;

// Temporary client stuff.
class Mesh;
class MeshGroup;
class Shader;
class Texture;
class Material;

class PhysicsEngine;
class Entity;
class PhysicsBody2D;
class RigidBody2D;
class Collider2D;

class NotAnEngineCore
{
public:
	NotAnEngineCore(const char* title, unsigned int width, unsigned int height);
	~NotAnEngineCore();

	void Run();

private:
	void OnEvent(Event& event);
	void Terminate();

	Window* _window;
	bool _hasTerminated;
protected:
	void SetClearColor(float r, float g, float b, float a);

	// Should be pure virtual and derived from client sided project. 
	virtual void OnStart();
	virtual void OnUpdate(float deltaTime);
	virtual void OnFixedUpdate(float timeStep);
	virtual void OnShutdown();

	Renderer* _renderer;
	Camera* _mainCamera;

	PhysicsEngine* _physicsEngine;
	Entity* _circleEntity;
	Entity* _circleEntity2;
	Entity* _squareEntity;
	Entity* _squareEntity2;
};