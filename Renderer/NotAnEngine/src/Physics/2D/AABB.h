#pragma once
#include "Collider2D.h"
#include "glm.hpp"

class Entity;

class AABB : public Collider2D
{
public:
	AABB(glm::vec2 size)
	{
		_extents = size / 2.0f;
	}

	virtual Shape2D GetColliderType() override { return Shape2D::AABB; }

	glm::vec2 GetMax()
	{
		return _position + _extents;
	}

	glm::vec2 GetMin()
	{
		return _position - _extents;
	}

	glm::vec2 GetExtents()
	{
		return _extents;
	}

private:
	glm::vec2 _extents; // Half size of AABB
};