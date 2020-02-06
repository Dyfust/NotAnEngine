#include "glm.hpp"
#include "ext.hpp"
#pragma once

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;

	Vertex(glm::vec3 position, glm::vec3 normal);
	Vertex(glm::vec3 position);
};