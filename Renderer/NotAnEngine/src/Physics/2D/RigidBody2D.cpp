#include "RigidBody2D.h"
#include "../../Entity.h"
#include "../../glm/glm.hpp"

RigidBody2D::RigidBody2D(Entity* transform, Collider2D* collider, float mass, float elasticity) : PhysicsBody2D(transform, collider)
{
	_mass = mass;
    _elasticity = elasticity;
	_velocity = glm::vec2(0.0f, 0.0f);
}

void RigidBody2D::FixedUpdate(glm::vec2 gravity, float fixedTimeStep)
{
	AddForce(gravity * _mass * fixedTimeStep);
	_transform->Translate(glm::vec3(_velocity, 0.0f) * fixedTimeStep);
}

void RigidBody2D::AddForce(glm::vec2 force)
{
	glm::vec2 acceleration = force / _mass;
	_velocity += acceleration;
}

void RigidBody2D::ApplyForceToObject(RigidBody2D* object, glm::vec2 force)
{
    object->AddForce(force);
    this->AddForce(-force);
}

void RigidBody2D::ResolveCollision(RigidBody2D* other, glm::vec2 collisionNormal)
{
    glm::vec2 normal = glm::normalize(collisionNormal);
    glm::vec2 relativeVelocity = other->_velocity - _velocity;

    float j =
        glm::dot(-(1 + (_elasticity * other->_elasticity)) * (relativeVelocity), normal)
        /
        glm::dot(normal, normal * ((1 / _mass) + (1 / other->_mass)));

    glm::vec2 force = normal * j;

    ApplyForceToObject(other, force);
}

void RigidBody2D::ResolveCollision(PhysicsBody2D* other, glm::vec2 collisionNormal)
{
    glm::vec2 normal = glm::normalize(collisionNormal);
    glm::vec2 relativeVelocity = -_velocity;

    float j =
        glm::dot(-(1 + _elasticity) * (relativeVelocity), normal)
        /
        glm::dot(normal, normal * (1 / _mass));

    glm::vec2 force = normal * j;

    AddForce(-force);
}

void RigidBody2D::SetVelocity(glm::vec2 velocity)
{
    _velocity = velocity;
}

glm::vec2 RigidBody2D::GetVelocity() const
{
    return _velocity;
}
