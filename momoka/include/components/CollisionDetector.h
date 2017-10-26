#pragma once
#include <vector>
#include "elements/tile.h"
#include "components/PhysicalBody.h"


enum COLLISION_FLAG { Collision_left, Collision_right, Collision_up, Collision_down, Collision_none };

struct TileCollisionInfo {
	COLLISION_FLAG flag;
	TileMapKey tileMapKey;
	TileType tileType;
};

typedef std::vector<TileCollisionInfo> TileCollisionInfoVector;

class CollisionDetector {
public:
	explicit CollisionDetector(TileMap& tileMap, TileTpyeMap& tileTpyeMap);
	~CollisionDetector();

	TileCollisionInfoVector TileCollisionChecker(const PhysicalBody& physicalBody) const;
	PhysicalBody TileCollisionDefaultSolver(const TileCollisionInfo& tileCollisionInfo, PhysicalBody physicalBody);

private:
	const TileMap& m_tileMap_;
	const TileTpyeMap& m_tileTypeMap_;

	inline TileCollisionInfo GenerateTileCollisionInfo(COLLISION_FLAG flag, TileMapKey key) const;
};
