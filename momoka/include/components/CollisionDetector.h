#pragma once
#include "elements/tile.h"
#include "components/PhysicalBody.h"


enum COLLISION_FLAG { Collision_left, Collision_right, Collision_up, Collision_down, Collision_none };

struct TileCollisionInfo {
	COLLISION_FLAG flag;
	TileMapKey tileMapKey;
};

class CollisionDetector {
public:
	CollisionDetector();
	~CollisionDetector();

	const TileKeyVector& EntityToTile(PhysicalBody& physicalBody);
private:
	TileKeyVector m_tileKeyVector_;
};
