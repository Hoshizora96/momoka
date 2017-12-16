#pragma once
#include "Core.h"
#include <vector>
#include "object/EntityPool.h"
#include "map/TilePool.h"
#include "core/object/GameObjectPool.h"
#include "core/tools/Camera.h"

#include "factory/HeroFactory.h"
#include "factory/MonsterFactory.h"
#include "factory/PropFactory.h"
#include "system/MoveSystem.h"
#include "system/PlayerControlSystem.h"
#include "system/WorldObstacleSystem.h"
#include "system/RenderSystem.h"
#include "system/GravitySystem.h"
#include "system/DamageSystem.h"
#include "system/DeadSystem.h"
#include "system/PickPropSystem.h"
#include "system/MonsterAISystem.h"

#include "Engine.h"
#include "services/GraphicService.h"

class GameCore : public Core {
public:
	GameEntityPool entityPool;
	TilePool tilePool;

	Camera camera;

	std::vector<System*> systems;

	GravitySystem gravitySystem;
	MoveSystem moveSystem;
	PlayerControlSystem playerControlSystem;
	WorldObstacleSystem worldObstacleSystem;
	RenderSystem renderSystem;
	DamageSystem damageSystem;
	DeadSystem deadSystem;
	PickPropSystem pickpropSystem;
	MonsterAISystem monsterAISystem;

	ID2D1Bitmap* heroBitmap;

	GameCore();
	void Initialize();

	void Update(float& dt) override;

private:

	template <typename T, typename U, typename ... TSystems>
	void InitializeSystem();

	template <typename T>
	void InitializeSystem();


};


template <typename T, typename U, typename ... TSystems>
void GameCore::InitializeSystem() {
	System* t = static_cast<System*>(new T());
	t->Initialize(this);
	systems.push_back(t);
	InitializeSystem<U, TSystems...>();
}

template <typename T>
void GameCore::InitializeSystem() {
	System* t = static_cast<System*>(new T());
	t->Initialize(this);
	systems.push_back(t);
}

inline GameCore::GameCore() {
	Initialize();
}

inline void GameCore::Initialize() {

	InitializeSystem<
		GravitySystem,
		MoveSystem,
		PlayerControlSystem,
		WorldObstacleSystem,
		RenderSystem,
		DamageSystem,
		DeadSystem,
		PickPropSystem
	>();

	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();

	graphicService->LoadBitMap(L"content/assert/40.png", &heroBitmap);

	HeroFactory heroFactroy;
	heroFactroy.Create(entityPool);

	MonsterFactory monsterFactroy;
	monsterFactroy.Create(entityPool, 0);

	PropFactory propFactory;
	propFactory.Create(entityPool, 0);
	propFactory.Create(entityPool, 1);

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

	LONGLONG begin = 0, end = 0;


	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "Entities num: " << entityPool.AliveNum();
	}

	begin = GetCurrentTick();
	gravitySystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "gravitySystem: " << (end - begin) * 1000 / Engine::freq;
	}

	begin = GetCurrentTick();
	playerControlSystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "playerControlSystem: " << (end - begin) * 1000 / Engine::freq;
	}

	begin = GetCurrentTick();
	moveSystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "moveSystem: " << (end - begin) * 1000 / Engine::freq;
	}

	begin = GetCurrentTick();
	worldObstacleSystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "worldObstacleSystem: " << (end - begin) * 1000 / Engine::freq;
	}

	begin = GetCurrentTick();
	damageSystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "damageSystem: " << (end - begin) * 1000 / Engine::freq;
	}

	begin = GetCurrentTick();
	renderSystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "renderSystem: " << (end - begin) * 1000 / Engine::freq;
	}

	begin = GetCurrentTick();
	deadSystem.Update(dt, *this);
	end = GetCurrentTick();
	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug) << "deadSystem: " << (end - begin) * 1000 / Engine::freq << std::endl;
	}


	//	gravitySystem.Update(dt, *this);
	//	playerControlSystem.Update(dt, *this);
	//	moveSystem.Update(dt, *this);
	//	worldObstacleSystem.Update(dt, *this);
	//	damageSystem.Update(dt, *this);
	//	renderSystem.Update(dt, *this);
	//	deadSystem.Update(dt, *this);
	pickpropSystem.Update(dt, *this);
	monsterAISystem.Update(dt, *this);
	
}
