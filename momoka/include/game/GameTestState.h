#pragma once
#include "util/HandleTable.h"
#include "game/GameState.h"
#include "util/ServiceLoader.h"
#include "objects/Entity.h"
#include "objects/Tile.h"
#include "objects/Hero.h"
#include <list>
#include <map>
#include <vector>

class GameTestState : public GameState {
public:
	explicit GameTestState(ServiceLoader& serviceLoader);
	~GameTestState();

	void OnEnter() override;
	void OnExit() override;
	void Render(float dt) override;
	void Update() override;

	momoka::HandleTable<Entity*> m_handleTable;
	std::list<int> m_actorList;
	std::map<int, TileInfo> m_tileInfoMap;
	std::vector<Tile> m_tiles;

	Hero* m_pPlayerCharacter;
private:
	void WorldLoader();
};
