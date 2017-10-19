#include "stdafx.h"
#include "components/CollisionDetector.h"
#include "components/PhysicalBody.h"


const TileKeyVector& CollisionDetector::EntityToTile(PhysicalBody& physicalBody) {
	m_tileKeyVector_.clear();

	/* 当一个entity在左边或上边与tile相邻但未重合时，由于查找坐标所在位置对应tile时是用的整除法
	 * （x:=40, y:=40，x/40=1, y/40=1，虽然(1,1)处没有tile，但是不知道(1,0）或(0,1)处是否有tile）
	 * 所以检查entity左边或上边tile时不会知道与其相邻，但这种情况也属于碰撞，
	 * 解决方法：如果entity具有向上或向左的速度分量，就在对应方向上加一个位置偏移，使其与左边或上边的tile重合，进而能够进行碰撞检测 */

	const auto defaultTileInfo = GetDefaultTileInfo();

	auto x = physicalBody.posX;
	auto y = physicalBody.posY;

	auto vx = physicalBody.velocityX;
	auto vy = physicalBody.velocityY;

	if (vx < 0) x -= 0.1;
	if (vy < 0) y -= 0.1;

//	// 触碰到地图左边界
//	if (x <= 0 && vx < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo);
//		entity->SetX(0);
//	}
//
//	// 触碰到地图上边界
//	if (y <= 0 && vy < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo);
//		entity->SetY(0);
//	}

	return m_tileKeyVector_;
}
