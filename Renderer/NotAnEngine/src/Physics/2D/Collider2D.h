#pragma once
#include "glm.hpp"

class Collider2D 
{
public:
	enum class Collider2DType { CIRCLE, AABB, LINE };

	Collider2D(glm::vec2 position) : _position(position)
	{ }

	virtual Collider2DType GetColliderType() = 0;

	void SetPosition(glm::vec2 position)
	{ _position = position; }

protected:
	glm::vec2 _position;
};