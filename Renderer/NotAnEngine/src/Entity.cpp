#include "Entity.h"
#include <iostream>

void Entity::UpdateWorldMatrix()
{
	if (_parent != nullptr)
		_worldMatrix = _parent->_worldMatrix * _localMatrix;
	else
		_worldMatrix = _localMatrix;

	UpdateChildrenWorldMatrix()
}

void Entity::UpdateChildrenWorldMatrix()
{
	for (auto c : _children)
	{
		c->UpdateWorldMatrix();
	}
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

void Entity::SetParent(Entity* parent)
{
	// Parent validation.
	if (parent == this || std::find(_children.begin(), _children.end(), parent) == _children.end) 
	{
		std::cout << "Cannot be parented to itself or a child." << std::endl;
		return;
	}

	_parent = parent;
}

void Entity::AddChild(Entity* child)
{
	if (child == _parent || std::find(_children.begin(), _children.end(), child) == _children.end)
	{
		std::cout << "The parent cannot be a child, or the child already exists." << std::endl;
		return;
	}

	_children.push_back(child);
}