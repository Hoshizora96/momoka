#pragma once
#include "core/system/System.h"
#include "core/object/GameObjectPool.h"
#include "util/Direction.h"

class WorldObstacleSystem : public System {
public:
	void Update(float& dt, GameCore& core) override;
	static bool IsOnTileLine(float o);

private:
	void TakeObstacle(GameEntityPool::Entity& entity, DIRECTION direction, float correntPosition);
};
