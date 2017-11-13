#pragma once
#include "components/Direction.h"
#include "map/TileType.h"

class CollisionInfo {
public:
	bool isOnGround;

	bool isCollisionX;
	bool isCollisionY;

	Direction directionX;
	Direction directionY;
	
	int tileType;
	int tileX;
	int tileY;
	
	int correctedX;
	int correctedY;

	float inheritedVelocityX;
	float inheritedVelocityY;

	CollisionInfo();

	void ClearAllFlag();
	void SetCollision(Direction dir, float corrected);
};