#pragma once
#include "util/HandleTable.h"
#include "game/GameState.h"
#include "objects/Entity.h"
#include "util/TileInfo.h"
#include "objects/Hero.h"
#include "commands/Command.h"

#include <list>
#include <unordered_map>

class GameTestState : public GameState {
public:
	GameTestState();
	~GameTestState() override;

	void OnEnter() override;
	void OnExit() override;
	void Render(float dt) override;
	void Update() override;

private:
//	momoka::HandleTable<Entity*> m_handleTable_;
	std::list<int> m_actorList_;
	std::unordered_map<int, TileInfo> m_tileInfoMap_;
	std::unordered_map<__int64, int> m_tiles_;

	Hero* m_pPlayerCharacter_;
	void WorldLoader();
	void GlobalPhysicsSimulation(Entity* entity);
	void EntityInit(Entity* entity);

	static __int64 TileMapKeyConvert(__int64 xTile, __int64 yTile);

	Command* m_commandW_;
	Command* m_commandA_;
	Command* m_commandS_;
	Command* m_commandD_;
};


