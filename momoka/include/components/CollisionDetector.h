#pragma once
#include "components/CollisionInfo.h"
#include "map/TileSet.h"
#include "components/PhysicalBody.h"
#include "HitBox.h"

class CollisionDetector {
public:
	explicit CollisionDetector(TileSet& tileSet);
	
	// 检测body与tile的固体碰撞，这意味着会发生阻挡
	CollisionInfo CheckTileCollision(PhysicalBody &body) const;
	bool CheckHitBoxCollison(HitBox myHitBox, HitBox opponentHitBox);
	// bool CheckCollision();
private:
	// 用来检测某一坐标值是否位于Tile边界上
	static bool IsOnTileLine(float o);
	TileSet& m_tileSet;
};
