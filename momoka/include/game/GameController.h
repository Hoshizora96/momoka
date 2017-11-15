#pragma once
#include "game/GameState.h"

class GameController {
public:
	GameController();
	~GameController();
	
	void Update(float dt);
	void Render(float dt);

	void Initialize();
	void Shutdown();

	void SwitchGameState(int state);

private:
	GameState* m_pGameState_;
};