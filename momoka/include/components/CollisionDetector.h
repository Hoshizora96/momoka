#pragma once
#include "components/CollisionInfo.h"
#include "map/TileSet.h"
#include "components/PhysicalBody.h"

class CollisionDetector {
public:
	explicit CollisionDetector(TileSet& tileSet);
	CollisionInfo CheckTileCollision(PhysicalBody &body) const;
	bool CheckCollision();
private:
	TileSet& m_tileSet_;
};