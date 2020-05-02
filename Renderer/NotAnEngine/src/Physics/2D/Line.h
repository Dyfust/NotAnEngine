#pragma once
#include "Collider2D.h"
#include "glm.hpp"

class Entity;

class Line : public Collider2D
{
public:
	Line(glm::vec2 normal, float distance) : _normal(normal), _distance(distance)
	{ }

	virtual Shape2D GetColliderType() override { return Shape2D::Line; }
	glm::vec2 GetNormal() const;

private:
	friend class CollisionManager2D;

	glm::vec2 _normal;
	float _distance;
};