#pragma once
#include "../../Entity.h"
#include "glm.hpp"


class Collider2D 
{
public:
	enum class Shape2D : char
	{
		Circle = 0,
		AABB,
		Line,
		Count
	};

	Collider2D()
	{ }

	virtual Shape2D GetColliderType() = 0;

	void SetPosition(glm::vec2 position)
	{
		_position = position;
	}

	glm::vec2 GetPosition() { return _position; }

protected:
	friend class CollisionManager2D;
	glm::vec2 _position;
};