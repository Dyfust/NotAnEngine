#pragma once
#include "Collider2D.h"

class Circle : public Collider2D
{
public:
	Circle(glm::vec2 position, float radius) : Collider2D(position), _radius(radius)
	{ }

	virtual Collider2DType GetColliderType() override { return Collider2DType::CIRCLE; }

private:
	float _radius;
};