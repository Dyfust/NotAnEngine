#pragma once
#include "Collider2D.h"
#include "../../Entity.h"
#include "glm.hpp"

class PhysicsBody2D
{
public:
	PhysicsBody2D(Entity* transform, Collider2D* collider) 
	{
		_transform = transform;
		_collider = collider;
	}

	virtual ~PhysicsBody2D()
	{

	}

	void SetPosition(glm::vec3 position)
	{
		_transform->SetPosition(position);
	}

	glm::vec3 GetPosition() const
	{
		return _transform->GetPosition();
	}
	
	Collider2D* GetCollider() const
	{
		return _collider;
	}

protected:
	Entity* _transform;
	Collider2D* _collider;
};