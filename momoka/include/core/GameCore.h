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
#include "system/BulletStorageControlSystem.h"

#include "Engine.h"
#include "services/GraphicService.h"

#include "core/object/GroupManager.h"
#include "core/object/GameGroupSet.h"

#include "core/tools/Gui.h"
#include "system/GuiSystem.h"
#include "tools/animator/HeroAnimator.h"

class GameCore : public Core {
public:
	GameEntityPool entityPool;
	TilePool tilePool;
	GameGroupSet groupManager;

	Camera camera;

	std::vector<System*> systems;

	ID2D1Bitmap* heroBitmap;

	Gui gui;

	HeroAnimator heroAnimator;

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

inline GameCore::GameCore() : entityPool(),
                              groupManager(GameGroupSet(&entityPool)) {
	Initialize();
}

inline void GameCore::Initialize() {

	// 注意这个是有严格的顺序要求的
	InitializeSystem<
		GravitySystem,
		MoveSystem,
		PlayerControlSystem,
		WorldObstacleSystem,
		DamageSystem,
		PickPropSystem,
		MonsterAISystem,
		RenderSystem,
		DeadSystem,
		BulletStorageControlSystem
	>();

//	heroAnimator.LoadAnimationSet(L"content/asset/hero-frame-set.png");

	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();

	graphicService->LoadBitMap(L"content/asset/40.png", &heroBitmap);

	HeroFactory heroFactroy;
	heroFactroy.Create(entityPool);

	MonsterFactory monsterFactroy;
	monsterFactroy.Create(entityPool, 0);

	PropFactory propFactory;
	propFactory.Create(entityPool, 0);
	propFactory.Create(entityPool, 2);

	for (int i = 0;i < 20;i++) {
		tilePool.AddTile(i, 11, 0);
	}
	tilePool.AddTile(4, 5, 0);
	tilePool.AddTile(5, 7, 0);
}

inline void GameCore::Update(float& dt) {

	if (Engine::aSecond) {
		MOMOKA_LOG(momoka::debug);
		MOMOKA_LOG(momoka::debug) << "Entities num: " << entityPool.AliveNum();
	}

	for (int i = 0; i < systems.size(); i++) {
		LONGLONG begin = GetCurrentTick();
		systems[i]->Update(dt);
		LONGLONG end = GetCurrentTick();
		if (Engine::aSecond) {
			MOMOKA_LOG(momoka::debug) << systems[i]->toString() << ": " << (end - begin) * 1000 / Engine::freq;
		}
	}
}
