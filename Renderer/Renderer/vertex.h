#include "glm.hpp"
#include "ext.hpp"
#pragma once

struct vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;

	vertex(glm::vec3 position, glm::vec3 normal);
	vertex(glm::vec3 position);
};

