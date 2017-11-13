#pragma once
#include "game/GameState.h"
#include "objects/Hero.h"
#include "objects/Entity.h"
#include "map/TileSet.h"
#include <list>

class GamePlayState : public GameState {

public:
	explicit GamePlayState();

	void OnEnter() override;
	void OnExit() override;
	void Render(float dt) override;
	void Update(float dt) override;

	bool LoadMap();

private:
//	Hero *m_hero_;
	TileSet m_tileSet_;
};
