#include "CollisionManager2D.h"

glm::vec2 CollisionManager2D::CircleToCircle(Collider2D* circle1, Collider2D* circle2)
{
	Circle* a = dynamic_cast<Circle*>(circle1);
	Circle* b = dynamic_cast<Circle*>(circle2);
	glm::vec2 displacement = (a->_position - b->_position);
	float sumOfRadius = a->_radius + b->_radius;
	float overlap = sumOfRadius - glm::length(displacement);

	if (overlap > 0.0f)
	{
		return glm::normalize(displacement) * overlap;
	}

	return glm::vec2(0.0f);
}

glm::vec2 CollisionManager2D::CircleToAABB(Collider2D* circle, Collider2D* aabb)
{
	Circle* a = dynamic_cast<Circle*>(circle);
	AABB* b = dynamic_cast<AABB*>(aabb);

	glm::vec2 clampedPosition = glm::clamp(a->_position, b->GetMin(), b->GetMax());
	
	glm::vec2 displacement = clampedPosition - a->GetPosition();

	float overlap = a->GetRadius() - glm::length(displacement);

	if (overlap > 0.0f)
	{
		return -glm::normalize(displacement) * overlap;
	}
	else
		return glm::vec2(0.0f);
}

glm::vec2 CollisionManager2D::CircleToLine(Collider2D* circle, Collider2D* line)
{
	Circle* a = dynamic_cast<Circle*>(circle);
	Line* b = dynamic_cast<Line*>(line);

	float pDotN = glm::dot(a->_position, b->_normal);

	float distance = pDotN - (b->_distance + a->_radius);

	if (distance < 0.0f)
		return -(b->_normal * distance);
	else
		return glm::vec2(0.0f);
}

glm::vec2 CollisionManager2D::AABBToCircle(Collider2D* a, Collider2D* b)
{
	return CircleToAABB(b, a);
}

glm::vec2 CollisionManager2D::AABBToAABB(Collider2D* aabb1, Collider2D* aabb2)
{
	AABB* a = dynamic_cast<AABB*>(aabb1);
	AABB* b = dynamic_cast<AABB*>(aabb2);

	const float max_overlap = 10000000.0f;
	float overlap = max_overlap; //<- numeric float limit would be a better choice

	glm::vec2 overlap_vector = glm::vec2(0.0f);


	// Given A and B are aabbs, lets check each axis for an overlap.
	if (a->GetMax().x > b->GetMin().x)
	{
		float local_overlap = abs(a->GetMax().x - b->GetMin().x);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			overlap_vector = glm::vec2(-overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	// Check the other side
	if (a->GetMin().x < b->GetMax().x)
	{
		float local_overlap = abs(a->GetMin().x - b->GetMax().x);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			// Other direction along x
			overlap_vector = glm::vec2(overlap, 0);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	// Y axis check
	if (a->GetMax().y > b->GetMin().y)
	{
		float local_overlap = abs(a->GetMax().y - b->GetMin().y);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			overlap_vector = glm::vec2(0, -overlap);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	// Check the other side
	if (a->GetMin().y < b->GetMax().y)
	{
		float local_overlap = abs(a->GetMin().y - b->GetMax().y);
		if (local_overlap < overlap)
		{
			overlap = local_overlap;
			// Other direction along y
			overlap_vector = glm::vec2(0, overlap);
		}
	}
	else
	{
		return glm::vec2(0.0f);
	}

	return overlap_vector;
}

glm::vec2 CollisionManager2D::AABBToLine(Collider2D* aabb, Collider2D* line)
{
	AABB* a = dynamic_cast<AABB*>(aabb);
	Line* b = dynamic_cast<Line*>(line);

	glm::vec2 extents = a->GetExtents();
	glm::vec2 extentsNegX = 0.5f * glm::vec2(-a->GetExtents().x, a->GetExtents().y);

	float dotExtents = glm::dot(extents, b->GetNormal());
	float dotExtentsNegX = glm::dot(extentsNegX, b->GetNormal());
	float radius = fmaxf(fabsf(dotExtents), fabsf(dotExtentsNegX));

	Circle projection(radius);
	projection.SetPosition(a->GetPosition());
	return CircleToLine(&projection, b);
}

glm::vec2 CollisionManager2D::LineToCircle(Collider2D* a, Collider2D* b)
{
	return CircleToLine(b, a);
}

glm::vec2 CollisionManager2D::LineToAABB(Collider2D* a, Collider2D* b)
{
	return AABBToLine(b, a);
}

glm::vec2 CollisionManager2D::LineToLine(Collider2D* a, Collider2D* b)
{
	return glm::vec2(0.0f, 0.0f);
}
