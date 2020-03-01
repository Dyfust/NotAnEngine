#include "vertex.h"

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoord)
{
	this->position = position;
	this->normal = normal;
	this->texcoord = texcoord;
}

Vertex::Vertex()
{

}