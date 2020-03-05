#pragma once
#include "glm.hpp"

struct DirectionalLight
{
public:
	glm::vec3 position;
	glm::vec3 color;

	DirectionalLight(glm::vec3 position, glm::vec3 color) :
		position(position), color(color) {}
};

struct PointLight
{
	glm::vec3 position;
	glm::vec3 color;
	float constant;
	float linear;
	float quadratic;

	PointLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic):
		position(position), color(color), constant(constant), linear(linear), quadratic(quadratic) {}
};