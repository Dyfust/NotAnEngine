#include "Entity.h"
#include "Physics/2D/RigidBody2D.h"
#include "Physics/2D/Collider2D.h"
#include "Physics/2D/Circle.h"
#include <iostream>

void Entity::UpdateWorldMatrix()
{
	if (_parent != nullptr)
		_worldMatrix = _parent->_worldMatrix * _localMatrix;
	else
		_worldMatrix = _localMatrix;

	UpdateChildrenWorldMatrix();
}

void Entity::UpdateChildrenWorldMatrix()
{
	for (auto c : _children)
	{
		c->UpdateWorldMatrix();
	}
}

Entity::Entity()
{
	_parent = nullptr;
	_localMatrix = glm::mat4(1);
	UpdateWorldMatrix();
}

Entity::~Entity()
{

}

void Entity::SetPhysicsBody(PhysicsBody2D* physicsBody2D)
{
	_physicsBody2D = physicsBody2D;
}

void Entity::Translate(glm::vec3 translation)
{
	_localMatrix = glm::translate(_localMatrix, translation);
	UpdateWorldMatrix();
}

void Entity::Scale(glm::vec3 scale)
{
	_localMatrix = glm::scale(_localMatrix, scale);
	UpdateWorldMatrix();
}

void Entity::Rotate(glm::vec3 axis, float angle)
{
	// Quaternion rotation.
	_localMatrix = glm::rotate(_localMatrix, angle, axis);
	UpdateWorldMatrix();
}

void Entity::SetPosition(glm::vec3 position)
{
	_localMatrix[3] = glm::vec4(position, 1);
}

void Entity::SetParent(Entity* parent)
{
	// Validate the parent first.
	if (parent == this || std::find(_children.begin(), _children.end(), parent) == _children.end()) 
	{
		std::cout << "Cannot be parented to itself or a child." << std::endl;
		return;
	}

	_parent = parent;
}

void Entity::AddChild(Entity* child)
{
	// Validate the child first.
	if (child == _parent || std::find(_children.begin(), _children.end(), child) == _children.end())
	{
		std::cout << "The parent cannot be a child, or the child already exists." << std::endl;
		return;
	}

	_children.push_back(child);
}

glm::mat4 Entity::GetWorldMatrix() const
{
	return _worldMatrix;
}

glm::vec3 Entity::GetPosition() const
{
	return _worldMatrix[3];
}

PhysicsBody2D& Entity::GetPhysicsBody() const
{
	return *_physicsBody2D;
}
