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
class Shader;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render(const Mesh& mesh, Material& material, glm::mat4 modelMatrix);
	void Render(const MeshGroup& meshGroup, Material& material, glm::mat4 modelMatrix);
	void RenderQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);
	void RenderCircle(glm::vec2 position, float radius, glm::vec4 color);
	void SetCamera(Camera* ptr);

private:
	Camera* _camera = nullptr;
	UniformBuffer* _uniformBuffer = nullptr;
	DirectionalLight* _directionalLight = nullptr;

	Mesh* _quadPrimitive;
	Mesh* _circlePrimitive;

	Shader* _primitivesShader;
	Material* _primitivesMaterial;

	glm::vec4 _primitivesColor;
};