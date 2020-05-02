#pragma once
#include "glm.hpp"
#include <vector>
#include <functional>

class PhysicsBody2D;
class Collider2D;

class PhysicsEngine
{
public:
using CollisionFunction = std::function<glm::vec2(Collider2D* a, Collider2D* b)>;
	PhysicsEngine(glm::vec2 gravity, float fixedTimeStep);
	~PhysicsEngine();

	void AddPhysicsBody2D(PhysicsBody2D* physicsBody);
	void RemovePhysicsBody2D(PhysicsBody2D* physicsBody); // Maybe? Once a physics object, always a physics object!

	void Update(float deltaTime);

private:
	std::vector<PhysicsBody2D*> _2DPhysicsBodies;
	float _fixedTimeStep;
	float _accumulatedTime;

	glm::vec2 _gravity;

protected:
	static CollisionFunction CollisionFunctions[];
};