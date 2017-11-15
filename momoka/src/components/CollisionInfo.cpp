#include "stdafx.h"
#include "components/CollisionInfo.h"
#include "map/TileSet.h"
#include "util/Log.h"


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

	correctedVelocityX = 0;
	correctedVelocityY = 0;
}

void CollisionInfo::SetCollision(Direction dir, float corrected) {
	switch (dir) {
	case Direction::Left:
	case Direction::Right:
		directionX = dir;
		isCollisionX = true;
		correctedX = corrected;
		correctedVelocityX = 0;
		// MOMOKA_LOG(momoka::debug) << (dir == Direction::Left ? "Collided at Left!" : "Collided at Right!");
		break;
	case Direction::Up:
	case Direction::Down:
		directionY = dir;
		isCollisionY = true;
		correctedY = corrected;
		correctedVelocityY = 0;
		if (dir == Direction::Down) { isOnGround = true; }
		break;
	default:
		break;
	}
}
