#include "stdafx.h"
#include "core/system/WorldObstacleSystem.h"
#include "core/GameCore.h"

void WorldObstacleSystem::Update(float& dt) {

	auto& obstacles = core->groupManager.GetGroup<groups::ObstacleGroup>();

	for(int i = 0; i < obstacles.Size(); i++) {
		auto entity = obstacles[i];
		auto positionPtr = entity.Get<PositionComponent>();
		auto obstaclePtr = entity.Get<ObstacleComponent>();
		auto velocityPtr = entity.Get<VelocityComponent>();

		obstaclePtr->xObstacle = false;
		obstaclePtr->yObstacle = false;

		float x = positionPtr->x;
		float y = positionPtr->y;
		float vx = velocityPtr->vx;
		float vy = velocityPtr->vy;
		float width = obstaclePtr->obstacleWidth;
		float height = obstaclePtr->obstacleHeight;

		// 因为沿着body的左边界和上边界查找无法找到与之恰好边界重合的tile，所以强行给它一个偏移
		if (vx < 0) x -= 0.1f;
		if (vy < 0) y -= 0.1f;

		if (x < 0 && vx < 0) {
			// 碰到左边界
			velocityPtr->vx = 0;
			positionPtr->x = 0;
			if (entity.Has<BulletComponent>()) {
				entity.Activate<DeadComponent>();
			}
		}

		if (y < 0 && vy < 0) {
			// 碰到上边界
			velocityPtr->vy = 0;
			positionPtr->y = 0;
			if (entity.Has<BulletComponent>()) {
				entity.Activate<DeadComponent>();
			}
		}

		__int64 xStartTile = int(x / momoka::TILE_SIZE);
		__int64 yStartTile = int(y / momoka::TILE_SIZE);
		__int64 xEndTile = int((x + width) / momoka::TILE_SIZE);
		__int64 yEndTile = int((y + height) / momoka::TILE_SIZE);

		auto correctedUp = (yStartTile + 1) * momoka::TILE_SIZE;
		auto correctedDown = yEndTile * momoka::TILE_SIZE - height;
		auto correctedLeft = (xStartTile + 1) * momoka::TILE_SIZE;
		auto correctedRight = xEndTile * momoka::TILE_SIZE - width;

		// 检测左下角块
		if (core->tilePool.HasTile(xStartTile, yEndTile)) {
			// info.tileType = m_tileSet_.GetTileTypeId(xStartTile, yEndTile);

			if (vx < 0 && vy > 0) {
				float dx = x - correctedLeft;
				float dy = y - correctedDown;
				if (abs(vy / vx) <= abs(dy / dx)) {
					TakeObstacle(entity, Left, correctedLeft);
				}
				else {
					TakeObstacle(entity, Down, correctedDown);
				}
			}
			else if (vy >= 0) {
				if (!IsOnTileLine(x)) {
					TakeObstacle(entity, Down, correctedDown);
				}
			}
			else if (vx < 0) {
				if (!IsOnTileLine(y + height)) {
					TakeObstacle(entity, Left, correctedLeft);
				}
			}
		}

		// 检测右下角块
		if (core->tilePool.HasTile(xEndTile, yEndTile)) {
			// info.tileType = m_tileSet_.GetTileTypeId(xEndTile, yEndTile);

			if (vx > 0 && vy > 0) {
				float dx = x - correctedRight;
				float dy = y - correctedDown;
				if (abs(vy / vx) <= abs(dy / dx)) {
					TakeObstacle(entity, Right, correctedRight);
				}
				else {
					TakeObstacle(entity, Down, correctedDown);
				}
			}
			else if (vy == 0) {
				TakeObstacle(entity, Down, correctedDown);
			}
			else if (vx > 0) {
				TakeObstacle(entity, Right, correctedRight);
			}
			else if (vy > 0) {
				if (!IsOnTileLine(x + width)) {
					TakeObstacle(entity, Down, correctedDown);
				}
			}

		}

		// 检测左上角块
		if (core->tilePool.HasTile(xStartTile, yStartTile)) {
			// info.tileType = m_tileSet_.GetTileTypeId(xStartTile, yStartTile);

			if (vx < 0 && vy < 0) {
				float dx = x - correctedLeft;
				float dy = y - correctedUp;
				if (abs(vy / vx) <= abs(dy / dx)) {
					TakeObstacle(entity, Left, correctedLeft);
				}
				else {
					TakeObstacle(entity, Up, correctedUp);
				}
			}
			else if (vx < 0) {
				TakeObstacle(entity, Left, correctedLeft);
			}
			else if (vy < 0) {
				TakeObstacle(entity, Up, correctedUp);
			}
		}

		// 检测右上角块
		if (core->tilePool.HasTile(xEndTile, yStartTile)) {
			// info.tileType = m_tileSet_.GetTileTypeId(xEndTile, yStartTile);

			if (vx > 0 && vy < 0) {
				float dx = x - correctedRight;
				float dy = y - correctedUp;
				if (abs(vy / vx) <= abs(dy / dx)) {
					TakeObstacle(entity, Right, correctedRight);
				}
				else {
					TakeObstacle(entity, Up, correctedUp);
				}
			}
			else if (vx > 0) {
				TakeObstacle(entity, Right, correctedRight);
			}
			else if (vy < 0) {
				if (!IsOnTileLine(x + width)) {
					TakeObstacle(entity, Up, correctedUp);
				}
			}
		}

		if (velocityPtr->vx == 0 && velocityPtr->vy == 0) {
			continue;
		}

		// 四条边的碰撞检测
		for (__int64 i = xStartTile; i < xEndTile; i++) {
			if (core->tilePool.HasTile(i, yStartTile)) {
				TakeObstacle(entity, Up, correctedUp);
				// info.tileType = m_tileSet_.GetTileTypeId(i, yStartTile);
				velocityPtr->vy = 0;
				positionPtr->y = correctedUp;
				break;
			}
			if (core->tilePool.HasTile(i, yEndTile)) {
				if (vy > 0) {
					TakeObstacle(entity, Down, correctedDown);
				}
				// info.tileType = m_tileSet_.GetTileTypeId(i, yEndTile);

				break;
			}
		}

		for (__int64 i = yStartTile + 1; i < yEndTile; i++) {
			if (core->tilePool.HasTile(xStartTile, i)) {
				TakeObstacle(entity, Left, correctedLeft);
				// info.tileType = m_tileSet_.GetTileTypeId(xStartTile, i);
				break;
			}
			if (core->tilePool.HasTile(xEndTile, i)) {
				TakeObstacle(entity, Right, correctedRight);
				// info.tileType = m_tileSet_.GetTileTypeId(xEndTile, i);
				break;
			}
		}

	}
}

bool WorldObstacleSystem::IsOnTileLine(float o) {
	return o - int(o) == 0 && int(o) % momoka::TILE_SIZE == 0;
}

void WorldObstacleSystem::TakeObstacle(GameEntityPool::Entity& entity, DIRECTION direction, float correntPosition) {
	auto positionPtr = entity.Get<PositionComponent>();
	auto obstaclePtr = entity.Get<ObstacleComponent>();
	auto velocityPtr = entity.Get<VelocityComponent>();
	if (entity.Has<BulletComponent>()) {
		entity.Activate<DeadComponent>();
	}
	if (direction == Left || direction == Right) {
		obstaclePtr->xObstacle = true;
		obstaclePtr->xDirection = direction;
		positionPtr->x = correntPosition;
		velocityPtr->vx = 0;
	}
	else {
		obstaclePtr->yObstacle = true;
		obstaclePtr->yDirection = direction;
		positionPtr->y = correntPosition;
		velocityPtr->vy = 0;
	}
	if (entity.Has<BulletComponent>()) {
		if(entity.Get<BulletComponent>()->bulletType != 3) //不是炸弹就直接消失
			entity.Activate<DeadComponent>();
	}

}

std::string WorldObstacleSystem::toString() {
	return std::string("world obstacle system");
}
