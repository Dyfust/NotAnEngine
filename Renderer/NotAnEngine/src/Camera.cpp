#include "camera.h"
#include "glfw3.h"

camera::camera()
{
	set_perspective(default_fov, default_aspect_ratio, default_near, default_far);
	set_lookat(glm::vec3(0.0, 0.0, -5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
}

camera::camera(float fov, float aspect_ratio, float near, float far)
{
	set_perspective(fov, aspect_ratio, near, far);
}

camera::~camera()
{
}

void camera::update_pv_transform()
{
	pv_matrix = projection_matrix * view_matrix;
}

void camera::set_perspective(float fov, float aspect_ratio, float near, float far)
{
	projection_matrix = glm::perspective(fov, aspect_ratio, near, far);
	update_pv_transform();
}

void camera::set_lookat(glm::vec3 from, glm::vec3 forward, glm::vec3 up)
{
	view_matrix = glm::lookAt(from, forward, up);
	world_matrix = glm::inverse(view_matrix);
	update_pv_transform();
}

void camera::set_position(glm::vec3 position)
{
	world_matrix[3] = glm::vec4(position, 1);
	view_matrix = glm::inverse(world_matrix);
	update_pv_transform();
}

void camera::update(float delta_time)
{
	glm::vec3 position = get_position();
	
	glm::vec2 input = glm::vec2(0.0f, 0.0f);
	GLFWwindow* context = glfwGetCurrentContext();
	
	if (glfwGetKey(context, GLFW_KEY_W) == GLFW_PRESS)
		input.y += 1;
	else if (glfwGetKey(context, GLFW_KEY_S) == GLFW_PRESS)
		input.y -= 1;

	if (glfwGetKey(context, GLFW_KEY_A) == GLFW_PRESS)
		input.x -= 1;
	else if (glfwGetKey(context, GLFW_KEY_D) == GLFW_PRESS)
		input.x += 1;

	glm::vec3 forward_direction = (glm::vec3)get_world_matrix()[2];
	glm::vec3 up_direction = (glm::vec3)get_world_matrix()[1];
	glm::vec3 right_direction = (glm::vec3)get_world_matrix()[0];

	glm::vec3 move_direction = -input.y * forward_direction + input.x * right_direction;
	glm::normalize(move_direction);
 
	position += move_direction * speed * delta_time;
	set_position(position);

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
		rotation = glm::rotate(rotation, float(angular_speed * delta_time * -delta_x), glm::vec3(view_matrix[1]));

		// Up / Down rotation
		rotation = glm::rotate(rotation, float(angular_speed * delta_time * -delta_y), glm::vec3(1.0f, 0.0f, 0.0f));
		// Apply the rotation to the camera
		world_matrix = world_matrix * rotation;
		// Update PxV
		update_pv_transform();
	}

}

const glm::mat4& camera::get_projection_matrix() const
{
	return projection_matrix;
}

const glm::mat4& camera::get_view_matrix() const
{
	return view_matrix;
}

const glm::mat4& camera::get_world_matrix() const
{
	return world_matrix;
}

const glm::mat4& camera::get_projection_vew_matrix() const
{
	return pv_matrix;
}

const glm::vec3& camera::get_position() const
{
	return glm::vec3(world_matrix[3]);
}