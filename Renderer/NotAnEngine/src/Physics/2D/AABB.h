#pragma once
#include "Collider2D.h"
#include "glm.hpp"

class AABB : public Collider2D
{
public:
	AABB(glm::vec2 position, glm::vec2 size) : Collider2D(position)
	{
		_extents = size / 2.0f;
	}

	virtual Collider2DType GetColliderType() override { return Collider2DType::AABB; }

private:
	glm::vec2 _extents; // Half size of AABB
};