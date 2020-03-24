#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Lights.h"

class Mesh;
class MeshGroup;
class Material;
class Camera;
class UniformBuffer;

class Renderer
{
public:
	Renderer();

	void Render(const Mesh& mesh, Material& material, glm::mat4 modelMatrix);
	void Render(const MeshGroup& meshGroup, Material& material, glm::mat4 modelMatrix);
	void SetCamera(Camera* ptr);

private:
	Camera* _camera = nullptr;
	UniformBuffer* _uniformBuffer = nullptr;
	DirectionalLight* _directionalLight = nullptr;
};