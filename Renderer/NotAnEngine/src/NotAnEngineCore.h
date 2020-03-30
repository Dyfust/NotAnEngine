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
	
	// Temporary client stuff.
	Shader* _shader2D;
	Texture* _spriteTexture;
	Material* _spriteMaterial;

	Shader* _shaderPhong;
	MeshGroup* _swordShield;

	Texture* _swordAlbedo;
	Texture* _swordNormal;

	Texture* _shieldAlbedo;
	Texture* _shieldNormal;

	Material* _swordMaterial;
	Material* _shieldMaterial;

	glm::vec4 _swordColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float _swordShininess = 0.25f;
	float _swordReflectance = 0.25f;

	glm::vec4 _shieldColor = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	float _shieldShininess = 0.6f;
	float _shieldReflectance = 1.0f;

	glm::mat4 _model = glm::mat4(1);

	Mesh* _sun;
	Texture* _sunAlbedo;
	Material* _sunMaterial;
};