#pragma once
#include "glm.hpp"
#include "ext.hpp"

class camera
{
private:
	glm::mat4 projection_matrix;
	glm::mat4 view_matrix;
	glm::mat4 world_matrix;
	glm::mat4 pv_matrix;

	const float default_fov = 90.0f * 3.14159f / 180.0f;
	const float default_aspect_ratio = 16.0f / 9.0f;
	const float default_near = 0.01f;
	const float default_far = 9999999999.0f;

	float speed = 20;
	float angular_speed = 0.1f;

	void update_pv_transform();

public:
	camera();
	camera(float fov, float aspect_ratio, float near, float far);
	~camera();

	void set_perspective(float fov, float aspect_ratio, float near, float far);
	void set_lookat(glm::vec3 from, glm::vec3 forward, glm::vec3 up);
	void set_position(glm::vec3 position);
	void update(float delta_time);
	const glm::mat4& get_projection_matrix() const;
	const glm::mat4& get_view_matrix() const;
	const glm::mat4& get_world_matrix() const;
	const glm::mat4& get_projection_vew_matrix() const;
	const glm::vec3& get_position() const;
};

