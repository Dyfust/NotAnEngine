#pragma once
#include "Collider2D.h"

class Entity;

class Circle : public Collider2D
{
public:
	Circle(float radius) : _radius(radius)
	{ }

	virtual Shape2D GetColliderType() override { return Shape2D::Circle; }

	float GetRadius() const
	{
		return _radius;
	}

private:
	friend class CollisionManager2D;
	float _radius;
};