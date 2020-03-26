#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include <vector>
#include <algorithm>

class Entity
{
private:
	// Maybe a scene graph is meant to be responsible for keeping track of parent/child relationships.
	Entity* _parent;
	std::vector<Entity*> _children;

	glm::mat4 _worldMatrix;
	glm::mat4 _localMatrix;

	void UpdateWorldMatrix();

	// Maybe a scene graph is meant to be responsible for this?
	void UpdateChildrenWorldMatrix();
public:
	void Translate(glm::vec3 translation);
	void Scale(glm::vec3 scale);
	void Rotate(glm::vec3 axis, float angle);

	void SetParent(Entity* parent);
	void AddChild(Entity* child);
};