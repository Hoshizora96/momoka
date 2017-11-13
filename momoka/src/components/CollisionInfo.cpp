#include "stdafx.h"
#include "components/CollisionInfo.h"
#include "map/TileSet.h"


CollisionInfo::CollisionInfo() {
	ClearAllFlag();
}

void CollisionInfo::ClearAllFlag() {
	isOnGround = false;

	isCollisionX = false;
	isCollisionY = false;

	directionX = Direction::Up;
	directionY = Direction::Down;

	tileX = 0;
	tileY = 0;

	tileType = 0;

	correctedX = 0;
	correctedY = 0;

	inheritedVelocityX = 0;
	inheritedVelocityY = 0;
}

void CollisionInfo::SetCollision(Direction dir, float corrected) {
	switch (dir) {
	case Direction::Left:
	case Direction::Right:
		directionX = dir;
		isCollisionX = true;
		correctedX = corrected;
		break;
	case Direction::Up:
	case Direction::Down:
		directionY = dir;
		isCollisionY = true;
		correctedY = corrected;
		break;
	default: 
		break;
	}
}
