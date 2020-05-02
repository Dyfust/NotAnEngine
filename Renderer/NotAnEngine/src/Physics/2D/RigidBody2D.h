#pragma once
#include "PhysicsBody2D.h"

class Entity;

class RigidBody2D : public PhysicsBody2D
{
public:
	RigidBody2D(Entity* transform, Collider2D* collider, float mass, float elasticity);

	virtual ~RigidBody2D() override
	{

	}

	void FixedUpdate(glm::vec2 gravity, float fixedTimeStep);
	void AddForce(glm::vec2 force);
	void ApplyForceToObject(RigidBody2D* object, glm::vec2 force);
	void ResolveCollision(RigidBody2D* other, glm::vec2 collisionNormal);
	void ResolveCollision(PhysicsBody2D* other, glm::vec2 collisionNormal);

	void SetVelocity(glm::vec2 velocity);
	glm::vec2 GetVelocity() const;

private:
	glm::vec2 _velocity;
	float _mass;
	float _elasticity;
};