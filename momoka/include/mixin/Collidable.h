#pragma once
#include "components/CollisionDetector.h"
class Collidable {
public:
	virtual ~Collidable() = default;
	virtual void HandleCollision(const CollisionDetector& collisionDetector) = 0;
};