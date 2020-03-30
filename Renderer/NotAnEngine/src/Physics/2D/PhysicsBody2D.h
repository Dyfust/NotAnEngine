#pragma once
#include "Collider2D.h"
#include "glm.hpp"

class PhysicsBody2D
{
public:
	PhysicsBody2D(/*Transform* transform*/ Collider2D* collider) 
	{
		_collider = collider;
		_colliderType = collider->GetColliderType();
	}

	~PhysicsBody2D()
	{
		delete _collider;
	}

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	Collider2D::Collider2DType GetColliderType() { return _colliderType; }

protected:
	/*Transform* _transform;*/
	Collider2D::Collider2DType _colliderType;
	Collider2D* _collider;
};