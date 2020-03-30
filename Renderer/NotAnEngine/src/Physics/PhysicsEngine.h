#pragma once
#include "glm.hpp"
#include <vector>

class PhysicsBody2D;

class PhysicsEngine
{
public:
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
};