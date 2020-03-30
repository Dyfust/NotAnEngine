#include "PhysicsEngine.h"
#include "2D/PhysicsBody2D.h"

PhysicsEngine::PhysicsEngine(glm::vec2 gravity, float fixedTimeStep)
{
	_fixedTimeStep = fixedTimeStep;
	_accumulatedTime = 0.0f;
	_gravity = gravity;
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::AddPhysicsBody2D(PhysicsBody2D* physicsBody)
{
	_2DPhysicsBodies.push_back(physicsBody);
}

void PhysicsEngine::RemovePhysicsBody2D(PhysicsBody2D* physicsBody)
{
	auto target = std::find(_2DPhysicsBodies.begin(), _2DPhysicsBodies.end(), physicsBody);
	_2DPhysicsBodies.erase(target);
}

void PhysicsEngine::Update(float deltaTime)
{
	_accumulatedTime += deltaTime;

	while (_accumulatedTime >= _fixedTimeStep)
	{
		for (auto p : _2DPhysicsBodies)
		{
			p->FixedUpdate(_gravity, _fixedTimeStep);
		}

		_accumulatedTime -= _fixedTimeStep;
	}
}
