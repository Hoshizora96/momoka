#pragma once
#include "game/GameState.h"
#include "util/ServiceLoader.h"

class GameTestState : public GameState {
public:
	GameTestState(ServiceLoader& serviceLoader);
	~GameTestState();

	void OnEnter() override;
	void OnExit() override;
	void Render() override;
	void Update(float dt) override;
};