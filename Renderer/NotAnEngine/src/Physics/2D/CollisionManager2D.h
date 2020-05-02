#pragma once
#include "Circle.h"
#include "AABB.h"
#include "Line.h"
#include "../../glm/glm.hpp"

class CollisionManager2D
{
public:
	static glm::vec2 CircleToCircle(Collider2D* a, Collider2D* b);
	static glm::vec2 CircleToAABB(Collider2D* a, Collider2D* b);
	static glm::vec2 CircleToLine(Collider2D* a, Collider2D* b);

	static glm::vec2 AABBToCircle(Collider2D* a, Collider2D* b);
	static glm::vec2 AABBToAABB(Collider2D* a, Collider2D* b);
	static glm::vec2 AABBToLine(Collider2D* a, Collider2D* b);

	static glm::vec2 LineToCircle(Collider2D* a, Collider2D* b);
	static glm::vec2 LineToAABB(Collider2D* a, Collider2D* b);
	static glm::vec2 LineToLine(Collider2D* a, Collider2D* b);
};