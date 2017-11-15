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

	// ！！！注意目前tileX和tileY暂时没有使用，也就是说碰撞发生后这两个值不会变化！！！
	int tileX;
	int tileY;
	
	int correctedX;
	int correctedY;

	float correctedVelocityX;
	float correctedVelocityY;

	CollisionInfo();

	void ClearAllFlag();
	void SetCollision(Direction dir, float corrected);
};