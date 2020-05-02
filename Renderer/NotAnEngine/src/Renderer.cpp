#include "Renderer.h"
#include "Mesh.h"
#include "MeshGroup.h"
#include "Material.h"
#include "Camera.h"
#include "UniformBuffer.h"
#include "Primitives.h"
#include "Shader.h"

Renderer::Renderer()
{
	_uniformBuffer = new UniformBuffer(5, sizeof(glm::mat4) + 3 * sizeof(glm::vec4), GL_DYNAMIC_DRAW);
	_directionalLight = new DirectionalLight(glm::vec3(20.0, 20.0, 20.0), glm::vec3(0.7f, 0.7f, 0.7f));

	// Set up primitives;
	_quadPrimitive = Primitives::GenerateQuad();
	_circlePrimitive = Primitives::GenerateCircle(1.0f, 50);

	_primitivesShader = new Shader("working\\Shaders\\2d_primitive_vertex.glsl", "working\\Shaders\\2d_primitive_frag.glsl");
	_primitivesShader->BindUniformBlock("Engine", 5.0);

	_primitivesMaterial = new Material(*_primitivesShader);
}

Renderer::~Renderer()
{
	delete _uniformBuffer;
	delete _directionalLight;
	delete _quadPrimitive;
	delete _circlePrimitive;
	delete _primitivesShader;
	delete _primitivesMaterial;
}

void Renderer::Render(const Mesh& mesh, Material& material, glm::mat4 modelMatrix)
{
	glm::vec3 tmp = _camera->GetPosition();
	glm::vec4 camera_pos = glm::vec4(tmp, 1.0f);
	glm::mat4 pvMatrix = _camera->GetProjectionViewMatrix();

	_uniformBuffer->UpdateBufferData(0, sizeof(glm::mat4), glm::value_ptr(pvMatrix));
	_uniformBuffer->UpdateBufferData(sizeof(glm::mat4), sizeof(glm::vec4), glm::value_ptr(camera_pos));
	// First directional light.
	_uniformBuffer->UpdateBufferData(sizeof(glm::mat4) + sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(_directionalLight->position, 1.0f)));
	_uniformBuffer->UpdateBufferData(sizeof(glm::mat4) + 2 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(_directionalLight->color, 1.0f)));

	material.SetValue("model_matrix", GL_FLOAT_MAT4, (void*)& modelMatrix);
	material.Bind();
	mesh.Bind();

	glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);

	material.Unbind();
	mesh.Unbind();
}

void Renderer::Render(const MeshGroup& meshGroup, Material& material, glm::mat4 modelMatrix)
{
	for (auto m : meshGroup.GetMeshes())
	{
		Render(*m, material, modelMatrix);
	}
}

void Renderer::RenderQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color)
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 0.0f));

	_primitivesColor = color;
	_primitivesMaterial->SetValue("color", GL_FLOAT_VEC4, (void*)&_primitivesColor);

	Render(*_quadPrimitive, *_primitivesMaterial, model);
}

void Renderer::RenderCircle(glm::vec2 position, float radius, glm::vec4 color)
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(glm::vec2(radius), 0.0f));

	_primitivesColor = color;
	_primitivesMaterial->SetValue("color", GL_FLOAT_VEC4, (void*)&_primitivesColor);

	Render(*_circlePrimitive, *_primitivesMaterial, model);
}

void Renderer::SetCamera(Camera* ptr)
{
	_camera = ptr;
}
