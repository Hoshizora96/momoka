#pragma once
#include "core/Core.h"

class GameController {
public:
	GameController();
	~GameController();
	
	void Update(float dt);

	void Initialize();
	void Shutdown();

	void SwitchGameState(int state);

private:
	Core* m_pGameState_;
};