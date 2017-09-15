#pragma once
#include "util/HandleTable.h"

class GameState {
public:
	virtual ~GameState() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Render(float dt) = 0;
	virtual void Update() = 0;
};
