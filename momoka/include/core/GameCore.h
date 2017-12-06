#pragma once
#include "Core.h"
#include "object/EntityPool.h"
#include "map/TilePool.h"
#include "core/object/GameObjectPool.h"

#include "factory/HeroFactory.h"
#include "system/MoveSystem.h"
#include "system/PlayerControlSystem.h"
#include "system/WorldObstacleSystem.h"
#include "system/RenderSystem.h"
#include "system/GravitySystem.h"

class GameCore : public Core{
public:
	GameEntityPool entityPool;
	TilePool tilePool;

	GravitySystem gravitySystem;
	MoveSystem moveSystem;
	PlayerControlSystem playerControlSystem;
	WorldObstacleSystem worldObstacleSystem;
	RenderSystem renderSystem;

	GameCore();

	void Initialize();
	void Update(float& dt) override;
};

inline GameCore::GameCore() {
	Initialize();
}

inline void GameCore::Initialize() {
	HeroFactory heroFactroy;
	heroFactroy.Create(entityPool);

	tilePool.AddTile(0, 9, 0);
	tilePool.AddTile(1, 9, 0);
	tilePool.AddTile(2, 9, 0);
	tilePool.AddTile(3, 9, 0);
	tilePool.AddTile(4, 9, 0);
	tilePool.AddTile(4, 5, 0);
	tilePool.AddTile(5, 9, 0);
	tilePool.AddTile(5, 7, 0);
	tilePool.AddTile(6, 9, 0);
}

inline void GameCore::Update(float& dt) {
	gravitySystem.Update(dt, *this);
	playerControlSystem.Update(dt, *this);
	moveSystem.Update(dt, *this);
	worldObstacleSystem.Update(dt, *this);
	renderSystem.Update(dt, *this);
}
