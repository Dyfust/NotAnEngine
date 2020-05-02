#include "PhysicsEngine.h"
#include "2D/PhysicsBody2D.h"
#include "2D/RigidBody2D.h"
#include "2D/CollisionManager2D.h"
#include <iostream>

PhysicsEngine::CollisionFunction PhysicsEngine::CollisionFunctions[] =
{
	CollisionManager2D::CircleToCircle, CollisionManager2D::CircleToAABB, CollisionManager2D::CircleToLine,
	CollisionManager2D::AABBToCircle, CollisionManager2D::AABBToAABB, CollisionManager2D::AABBToLine,
	CollisionManager2D::LineToCircle, CollisionManager2D::LineToAABB, CollisionManager2D::LineToLine
};

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
		for (PhysicsBody2D* p : _2DPhysicsBodies)
		{
			RigidBody2D* r = dynamic_cast<RigidBody2D*>(p);

			if (r)
				r->FixedUpdate(_gravity, _fixedTimeStep);
		}

		_accumulatedTime -= _fixedTimeStep;
	}

    for (int outer = 0; outer < _2DPhysicsBodies.size() - 1; outer++)
    {
        for (int inner = outer + 1; inner < _2DPhysicsBodies.size(); inner++)
        {
            PhysicsBody2D* object1 = _2DPhysicsBodies[outer];
            PhysicsBody2D* object2 = _2DPhysicsBodies[inner];
            Collider2D* collider1 = object1->GetCollider();
            Collider2D* collider2 = object2->GetCollider();
            Collider2D::Shape2D colliderType1 = collider1->GetColliderType();
            Collider2D::Shape2D colliderType2 = collider2->GetColliderType();

            // using function pointers
            int functionIdx = (int(colliderType1) * int(Collider2D::Shape2D::Count)) + int(colliderType2);
            CollisionFunction collisionFunctionPtr = CollisionFunctions[functionIdx];

            if (collisionFunctionPtr != nullptr)
            {
                // did a collision occur?
                collider1->SetPosition(object1->GetPosition());
                collider2->SetPosition(object2->GetPosition());
                auto result = collisionFunctionPtr(collider1, collider2);
                if (glm::length(result) > 0.001)
                {
                    // Dirty forces stop, remove asap
                    RigidBody2D* rigidBody1 = dynamic_cast<RigidBody2D*>(object1);
                    RigidBody2D* rigidBody2 = dynamic_cast<RigidBody2D*>(object2);

                    // Resolve collsion
                    // Separate
                    if (rigidBody1 && rigidBody2) // even split
                    {
                        rigidBody1->SetPosition(rigidBody1->GetPosition() + glm::vec3(result * 0.5f, 0));
                        rigidBody2->SetPosition(rigidBody2->GetPosition() - glm::vec3(result * 0.5f, 0));
                        rigidBody1->ResolveCollision(rigidBody2, result);
                    }
                    else if (rigidBody1)
                    {
                        rigidBody1->SetPosition(rigidBody1->GetPosition() + glm::vec3(result, 0));
                        rigidBody1->ResolveCollision(object2, result);
                    }
                    else if (rigidBody2)
                    {
                        rigidBody2->SetPosition(rigidBody2->GetPosition() + glm::vec3(result, 0));
                        rigidBody2->ResolveCollision(object1, result);
                    }
                }
            }
        }
    }
}
