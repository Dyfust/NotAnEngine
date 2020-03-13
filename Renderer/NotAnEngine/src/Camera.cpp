#include "camera.h"
#include "glfw3.h"

Camera::Camera()
{
	SetPerspective(_defaultFOV, _defaultAspectRatio, _defaultNear, _defaultFar);
	SetLookAt(glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0)); // Default
}

Camera::Camera(float fov, float aspect_ratio, float near, float far)
{
	SetPerspective(fov, aspect_ratio, near, far);
}

Camera::~Camera()
{}

void Camera::UpdatePVMatrix()
{
	_projectionViewMatrix = _projectionMatrix * _viewMatrix;
}

void Camera::SetPerspective(float fov, float aspectRatio, float near, float far)
{
	_projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
	UpdatePVMatrix();
}

void Camera::SetLookAt(glm::vec3 from, glm::vec3 forward, glm::vec3 up)
{
	_viewMatrix = glm::lookAt(from, forward, up);
	_worldMatrix = glm::inverse(_viewMatrix);
	UpdatePVMatrix();
}

void Camera::SetPosition(glm::vec3 position)
{
	_worldMatrix[3] = glm::vec4(position, 1);
	_viewMatrix = glm::inverse(_worldMatrix); // The view and world matrices are inverses of each other.
	UpdatePVMatrix();
}

void Camera::Update(float deltaTime)
{
	glm::vec3 position = GetPosition();
	
	glm::vec2 input = glm::vec2(0.0f, 0.0f);
	GLFWwindow* context = glfwGetCurrentContext();
	
	// Capture keyboard inputs for WASD.
	if (glfwGetKey(context, GLFW_KEY_W) == GLFW_PRESS)
		input.y += 1;
	else if (glfwGetKey(context, GLFW_KEY_S) == GLFW_PRESS)
		input.y -= 1;

	if (glfwGetKey(context, GLFW_KEY_A) == GLFW_PRESS)
		input.x -= 1;
	else if (glfwGetKey(context, GLFW_KEY_D) == GLFW_PRESS)
		input.x += 1;

	// Get the camera's orientation.
	glm::vec3 forward_direction = (glm::vec3)GetWorldMatrix()[2];
	glm::vec3 up_direction = (glm::vec3)GetWorldMatrix()[1];
	glm::vec3 right_direction = (glm::vec3)GetWorldMatrix()[0];

	glm::vec3 move_direction = -input.y * forward_direction + input.x * right_direction;
	glm::normalize(move_direction);
 
	position += move_direction * _speed * deltaTime;
	SetPosition(position);

	// Capture mouse position to rotate the camera.
	double cursor_position_x;
	double cursor_position_y;
	glfwGetCursorPos(context, &cursor_position_x, &cursor_position_y);

	double delta_x = cursor_position_x - (1280 * 0.5);
	double delta_y = cursor_position_y - (720 * 0.5);

	glfwSetCursorPos(context, 1280 * 0.5, 720 * 0.5);

	if (delta_x || delta_y)
	{
		// Identity matrix to accumulate rotation
		auto rotation = glm::mat4(1.0f);
		// Left / Right rotation
		rotation = glm::rotate(rotation, float(_angularSpeed * deltaTime * -delta_x), glm::vec3(_viewMatrix[1]));

		// Up / Down rotation
		rotation = glm::rotate(rotation, float(_angularSpeed * deltaTime * -delta_y), glm::vec3(1.0f, 0.0f, 0.0f));
		// Apply the rotation to the camera
		_worldMatrix = _worldMatrix * rotation;
		// Update PxV
		UpdatePVMatrix();
	}
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return _projectionMatrix;
}

const glm::mat4& Camera::GetViewMatrix() const
{
	return _viewMatrix;
}

const glm::mat4& Camera::GetWorldMatrix() const
{
	return _worldMatrix;
}

const glm::mat4& Camera::GetProjectionViewMatrix() const
{
	return _projectionViewMatrix;
}

const glm::vec3& Camera::GetPosition() const
{
	return glm::vec3(_worldMatrix[3]);
}