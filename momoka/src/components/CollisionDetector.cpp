#include "stdafx.h"
#include "components/CollisionDetector.h"
#include "util/Vector2.h"

CollisionDetector::CollisionDetector(TileSet& tileSet) : m_tileSet_(tileSet) {

}

CollisionInfo CollisionDetector::CheckTileCollision(PhysicalBody& body) const {
	// TODO: ÷ÿππ£°
	CollisionInfo info;
	auto position = body.GetPosition();
	auto velocity = body.GetVelocity();
	auto bodySize = body.GetBodySize();

	auto x = position.GetX();
	auto y = position.GetY();
	auto vx = velocity.GetX();
	auto vy = velocity.GetY();
	auto width = bodySize.GetX();
	auto height = bodySize.GetY();

	if (vx < 0) x -= 0.1f;
	if (vy < 0) y -= 0.1f;

	if (x < 0 && vx < 0) {
		info.correctedX = 0;
		info.directionX = Direction::Left;
		info.inheritedVelocityX = 0;
	}

	if (y < 0 && vy < 0) {
		info.correctedY = 0;
		info.directionY = Direction::Right;
		info.inheritedVelocityY = 0;
	}

	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
	__int64 xEndTile = int((x + width) / momoka_global::TILE_SIZE);
	__int64 yEndTile = int((y + height) / momoka_global::TILE_SIZE);

	auto correctedUp = (yStartTile + 1) * momoka_global::TILE_SIZE;
	auto correctedDown = yEndTile * momoka_global::TILE_SIZE - height;
	auto correctedLeft = (xStartTile + 1) * momoka_global::TILE_SIZE;
	auto correctedRight = xEndTile * momoka_global::TILE_SIZE - width;

	if (m_tileSet_.IsTileExist(xStartTile, yStartTile)) {
		info.tileType = m_tileSet_.GetTileTypeId(xStartTile, yStartTile);

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

	if (m_tileSet_.IsTileExist(xStartTile, yEndTile)) {
		info.tileType = m_tileSet_.GetTileTypeId(xStartTile, yEndTile);

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
			if ((x + width) - int(x + width) != 0) {
				info.SetCollision(Direction::Up, correctedUp);
			}
		}
	}

	if (m_tileSet_.IsTileExist(xStartTile, yEndTile)) {
		info.tileType = m_tileSet_.GetTileTypeId(xStartTile, yEndTile);

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
			info.SetCollision(Direction::Down, correctedDown);
		}
		else if (vx < 0) {
			info.SetCollision(Direction::Left, correctedLeft);
		}
	}

	if (m_tileSet_.IsTileExist(xEndTile, yEndTile)) {
		info.tileType = m_tileSet_.GetTileTypeId(xEndTile, yEndTile);

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
		if (vy == 0) {
			if ((x + width) - int(x + width) != 0) {
				info.SetCollision(Direction::Down, correctedDown);
			}
		}
		else if (vx > 0) {
			if ((y + height) - int(y + height) != 0) {
				info.SetCollision(Direction::Right, correctedRight);
			}
		}
		else if (vy > 0) {
			if ((x + width) - int(x + width) != 0) {
				info.SetCollision(Direction::Down, correctedDown);
			}
		}
	}

	for (__int64 i = yStartTile + 1; i < yEndTile; i++) {
		if (m_tileSet_.IsTileExist(xStartTile, y)) {
			info.SetCollision(Direction::Left, correctedLeft);
			info.tileType = m_tileSet_.GetTileTypeId(xStartTile, y);
			break;
		}
		if (m_tileSet_.IsTileExist(xEndTile, i)) {
			info.SetCollision(Direction::Right, correctedRight);
			info.tileType = m_tileSet_.GetTileTypeId(xEndTile, i);
			break;
		}
	}

	for (__int64 i = xStartTile + 1; i < xEndTile; i++) {
		if (m_tileSet_.IsTileExist(i, yStartTile)) {
			info.SetCollision(Direction::Up, correctedUp);
			info.tileType = m_tileSet_.GetTileTypeId(i, yStartTile);
			break;
		}
		if (m_tileSet_.IsTileExist(i, yEndTile)) {
			info.SetCollision(Direction::Down, correctedDown);
			info.tileType = m_tileSet_.GetTileTypeId(i, yEndTile);
			break;
		}
	}

	return info;
}
