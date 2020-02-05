#include "camera.h"

camera::camera()
{
	set_perspective(default_fov, default_aspect_ratio, default_near, default_far);
	set_lookat(glm::vec3(0, 0, 5), glm::vec3(0), glm::vec3(0, 1, 0));
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
	set_position(position - (glm::vec3(world_matrix[2]) * 0.05f));
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