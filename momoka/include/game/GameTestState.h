#pragma once
#include "util/HandleTable.h"
#include "game/GameState.h"
#include "objects/Entity.h"
#include "objects/Tile.h"
#include "objects/Hero.h"
#include "commands/Command.h"

#include <list>
#include <map>
#include <vector>



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
	std::map<int, TileInfo> m_tileInfoMap_;
	std::vector<Tile> m_tiles_;

	Hero* m_pPlayerCharacter_;
	void WorldLoader();

	Command* m_commandW_;
	Command* m_commandA_;
	Command* m_commandS_;
	Command* m_commandD_;
};


