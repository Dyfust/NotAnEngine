#include "glm.hpp"
#include "ext.hpp"
#pragma once

struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 tangent;
	glm::vec2 texcoord;

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec4 tangent, glm::vec2 texcoord);
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoord);
	Vertex();
};