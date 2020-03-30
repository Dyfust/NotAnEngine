#pragma once
#include "Collider2D.h"
#include "glm.hpp"

class Line : public Collider2D
{
public:
	Line(glm::vec2 normal, float distance) : Collider2D(glm::vec2(0.0f, 0.0f)), _normal(normal), _distance(distance)
	{ }

private:
	glm::vec2 _normal;
	float _distance;
};