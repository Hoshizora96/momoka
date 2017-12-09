#pragma once
#include "Core.h"
#include "object/EntityPool.h"
#include "map/TilePool.h"
#include "core/object/GameObjectPool.h"
#include "core/tools/Camera.h"

#include "factory/HeroFactory.h"
#include "factory/MonsterFactory.h"
#include "system/MoveSystem.h"
#include "system/PlayerControlSystem.h"
#include "system/WorldObstacleSystem.h"
#include "system/RenderSystem.h"
#include "system/GravitySystem.h"
#include "system/CollisionSystem.h"

class GameCore : public Core{
public:
	GameEntityPool entityPool;
	TilePool tilePool;

	Camera camera;

	GravitySystem gravitySystem;
	MoveSystem moveSystem;
	PlayerControlSystem playerControlSystem;
	WorldObstacleSystem worldObstacleSystem;
	RenderSystem renderSystem;
	CollisionSystem collisionSystem;

	ID2D1Bitmap* heroBitmap;

	GameCore();

	void Initialize();
	void Update(float& dt) override;

private:
	
};

inline GameCore::GameCore() {
	Initialize();
}

inline void GameCore::Initialize() {
	HeroFactory heroFactroy;
	heroFactroy.Create(entityPool);

	MonsterFactory monsterFactroy;
	monsterFactroy.Create(entityPool);

	tilePool.AddTile(0, 11, 0);
	tilePool.AddTile(1, 11, 0);
	tilePool.AddTile(2, 11, 0);
	tilePool.AddTile(3, 11, 0);
	tilePool.AddTile(4, 11, 0);
	tilePool.AddTile(4, 5, 0);
	tilePool.AddTile(5, 11, 0);
	tilePool.AddTile(5, 7, 0);
	tilePool.AddTile(6, 11, 0);
}

inline void GameCore::Update(float& dt) {
	gravitySystem.Update(dt, *this);
	playerControlSystem.Update(dt, *this);
	moveSystem.Update(dt, *this);
	worldObstacleSystem.Update(dt, *this);
	collisionSystem.Update(dt, *this);
	renderSystem.Update(dt, *this);
	
}
