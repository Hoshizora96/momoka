#include "stdafx.h"
#include "components/CollisionDetector.h"
#include "util/Vector2.h"
#include "util/Log.h"

CollisionDetector::CollisionDetector(TileSet& tileSet) : m_tileSet(tileSet) {

}

CollisionInfo CollisionDetector::CheckTileCollision(PhysicalBody& body) const {
	// TODO: 重构！

	/* 当一个entity在左边或上边与tile相邻但未重合时，由于查找坐标所在位置对应tile时是用的整除法
	* （x:=40, y:=40，x/40=1, y/40=1，虽然(1,1)处没有tile，但是不知道(1,0）或(0,1)处是否有tile）
	* 所以检查entity左边或上边tile时不会知道与其相邻，但这种情况也属于碰撞，
	* 解决方法：如果entity具有向上或向左的速度分量，就在对应方向上加一个位置偏移，使其与左边或上边的tile重合，进而能够进行碰撞检测 */

	// 截止2017/11/16，该函数正常工作，未发现问题
	CollisionInfo info;
	info.correctedX = body.GetPosition().GetX();
	info.correctedY = body.GetPosition().GetY();
	info.correctedVelocityX = body.GetVelocity().GetX();
	info.correctedVelocityY = body.GetVelocity().GetY();
	auto position = body.GetPosition();
	auto velocity = body.GetVelocity();
	auto bodySize = body.GetBodySize();

	auto x = position.GetX();
	auto y = position.GetY();
	auto vx = velocity.GetX();
	auto vy = velocity.GetY();
	auto width = bodySize.GetX();
	auto height = bodySize.GetY();

	// 因为沿着body的左边界和上边界查找无法找到与之恰好边界重合的tile，所以强行给它一个偏移
	if (vx < 0) x -= 0.1f;
	if (vy < 0) y -= 0.1f;

	if (x < 0 && vx < 0) {
		info.correctedX = 0;
		info.directionX = Direction::Left;
		info.correctedVelocityX = 0;
	}

	if (y < 0 && vy < 0) {
		info.correctedY = 0;
		info.directionY = Direction::Right;
		info.correctedVelocityY = 0;
	}

	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
	__int64 xEndTile = int((x + width) / momoka_global::TILE_SIZE);
	__int64 yEndTile = int((y + height) / momoka_global::TILE_SIZE);

	auto correctedUp = (yStartTile + 1) * momoka_global::TILE_SIZE;
	auto correctedDown = yEndTile * momoka_global::TILE_SIZE - height;
	auto correctedLeft = (xStartTile + 1) * momoka_global::TILE_SIZE;
	auto correctedRight = xEndTile * momoka_global::TILE_SIZE - width;

	// 检测左下角块
	if (m_tileSet.IsTileExist(xStartTile, yEndTile)) {
		info.tileType = m_tileSet.GetTileTypeId(xStartTile, yEndTile);

		if (vx < 0 && vy > 0) {
			float dx = x - correctedLeft;
			float dy = y - correctedDown;
			if (abs(vy / vx) <= abs(dy / dx)) {
				info.SetCollision(Direction::Left, correctedLeft);
			}
			else {
				info.SetCollision(Direction::Down, correctedDown);
			}
		}
		else if (vy >= 0) {
			if (!IsOnTileLine(x)) {
				info.SetCollision(Direction::Down, correctedDown);
			}
		}
		else if (vx < 0) {
			if (!IsOnTileLine(y + height)) {
				info.SetCollision(Direction::Left, correctedLeft);
			}
		}
	}

	// 检测右下角块
	if (m_tileSet.IsTileExist(xEndTile, yEndTile)) {
		info.tileType = m_tileSet.GetTileTypeId(xEndTile, yEndTile);

		if (vx > 0 && vy > 0) {
			float dx = x - correctedRight;
			float dy = y - correctedDown;
			if (abs(vy / vx) <= abs(dy / dx)) {
				info.SetCollision(Direction::Right, correctedRight);
			}
			else {
				info.SetCollision(Direction::Down, correctedDown);
			}
		}
		else if (vy == 0) {
			info.SetCollision(Direction::Down, correctedDown);
		}
		else if (vx > 0) {
			info.SetCollision(Direction::Right, correctedRight);
		}
		else if (vy > 0) {
			if (!IsOnTileLine(x + width)) {
				info.SetCollision(Direction::Down, correctedDown);
			}
		}

	}

	// 检测左上角块
	if (m_tileSet.IsTileExist(xStartTile, yStartTile)) {
		info.tileType = m_tileSet.GetTileTypeId(xStartTile, yStartTile);

		if (vx < 0 && vy < 0) {
			float dx = x - correctedLeft;
			float dy = y - correctedUp;
			if (abs(vy / vx) <= abs(dy / dx)) {
				info.SetCollision(Direction::Left, correctedLeft);
			}
			else {
				info.SetCollision(Direction::Up, correctedUp);
			}
		}
		else if (vx < 0) {
			info.SetCollision(Direction::Left, correctedLeft);
		}
		else if (vy < 0) {
			info.SetCollision(Direction::Up, correctedUp);
		}
	}

	// 检测右上角块
	if (m_tileSet.IsTileExist(xEndTile, yStartTile)) {
		info.tileType = m_tileSet.GetTileTypeId(xEndTile, yStartTile);

		if (vx > 0 && vy < 0) {
			float dx = x - correctedRight;
			float dy = y - correctedUp;
			if (abs(vy / vx) <= abs(dy / dx)) {
				info.SetCollision(Direction::Right, correctedRight);
			}
			else {
				info.SetCollision(Direction::Up, correctedUp);
			}
		}
		else if (vx > 0) {
			info.SetCollision(Direction::Right, correctedRight);
		}
		else if (vy < 0) {
			if(!IsOnTileLine(x+width)) {
				info.SetCollision(Direction::Up, correctedUp);
			}
		}
	}

	if (info.isCollisionX || info.isCollisionY) {
		return info;
	}

	// 四条边的碰撞检测
	for (__int64 i = xStartTile; i < xEndTile; i++) {
		if (m_tileSet.IsTileExist(i, yStartTile)) {
			info.SetCollision(Direction::Up, correctedUp);
			info.tileType = m_tileSet.GetTileTypeId(i, yStartTile);
			break;
		}
		if (m_tileSet.IsTileExist(i, yEndTile)) {
			info.SetCollision(Direction::Down, correctedDown);
			info.tileType = m_tileSet.GetTileTypeId(i, yEndTile);
			break;
		}
	}

	for (__int64 i = yStartTile; i < yEndTile; i++) {
		if (m_tileSet.IsTileExist(xStartTile, i)) {
			info.SetCollision(Direction::Left, correctedLeft);
			info.tileType = m_tileSet.GetTileTypeId(xStartTile, i);
			break;
		}
		if (m_tileSet.IsTileExist(xEndTile, i)) {
			info.SetCollision(Direction::Right, correctedRight);
			info.tileType = m_tileSet.GetTileTypeId(xEndTile, i);
			break;
		}
	}

	return info;
}

bool CollisionDetector::CheckHitBoxCollison(HitBox myHitBox, HitBox opponentHitBox) {
	return false;
}

bool CollisionDetector::IsOnTileLine(float o) {
	return o - int(o) == 0 && int(o) % momoka_global::TILE_SIZE == 0;
}
