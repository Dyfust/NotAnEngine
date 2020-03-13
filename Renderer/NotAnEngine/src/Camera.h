#pragma once
#include "glm.hpp"
#include "ext.hpp"

class Camera
{
private:
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _worldMatrix;
	glm::mat4 _projectionViewMatrix;

	const float _defaultFOV = 90.0f * 3.14159f / 180.0f;
	const float _defaultAspectRatio = 16.0f / 9.0f;
	const float _defaultNear = 0.01f;
	const float _defaultFar = 9999999999.0f;

	float _speed = 20;
	float _angularSpeed = 0.1f;

	void UpdatePVMatrix();
public:
	Camera();
	Camera(float fov, float aspect_ratio, float near, float far);
	~Camera();

	void SetPerspective(float fov, float aspect_ratio, float near, float far);
	void SetLookAt(glm::vec3 from, glm::vec3 forward, glm::vec3 up);
	void SetPosition(glm::vec3 position);
	void Update(float delta_time);
	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetWorldMatrix() const;
	const glm::mat4& GetProjectionViewMatrix() const;
	const glm::vec3& GetPosition() const;
};

