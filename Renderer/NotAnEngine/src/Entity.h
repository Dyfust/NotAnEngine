#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include <vector>
#include <algorithm>

class Collider2D;
class PhysicsBody2D;

class Entity
{
public:
	Entity();
	~Entity();

	void SetPhysicsBody(PhysicsBody2D* physicsBody);
	void Translate(glm::vec3 translation);
	void Scale(glm::vec3 scale);
	void Rotate(glm::vec3 axis, float angle);
	void SetPosition(glm::vec3 position);

	void SetParent(Entity* parent);
	void AddChild(Entity* child);

	glm::mat4 GetWorldMatrix() const;
	glm::vec3 GetPosition() const;
	PhysicsBody2D& GetPhysicsBody() const;

private:
	// Maybe a scene graph is meant to be responsible for keeping track of parent/child relationships.
	Entity* _parent;
	std::vector<Entity*> _children;

	glm::mat4 _worldMatrix;
	glm::mat4 _localMatrix;

	void UpdateWorldMatrix();
	// Maybe a scene graph is meant to be responsible for this?
	void UpdateChildrenWorldMatrix();

protected:
	// Components.
	PhysicsBody2D* _physicsBody2D;
};