#pragma once

class Window;
class Renderer;
class Camera;

// Temporary client stuff.
class Mesh;
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
	Mesh* _quad;
	Shader* _shader2D;
	Texture* _spriteTexture;
	Material* _spriteMaterial;
};