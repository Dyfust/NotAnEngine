#include "vertex.h"

vertex::vertex(glm::vec3 position, glm::vec3 normal)
{
	this->position = position;
	this->normal = normal;
}

vertex::vertex(glm::vec3 position)
{
	this->position = position;
	this->normal = glm::vec3(1, 0, 0);
}
