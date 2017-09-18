#include "stdafx.h"
#include "game/GameTestState.h"
#include "game/GameController.h"

GameController::GameController(): m_pGameState_(nullptr) {
}

GameController::~GameController() {
}

void GameController::Update() {
	m_pGameState_->Update();
}

void GameController::Render(float dt) {
	m_pGameState_->Render(dt);
}

void GameController::Initialize() {
}

void GameController::Shutdown() {
}

void GameController::SwitchGameState(int state) {
	if(state == 0) {
		m_pGameState_ = new GameTestState();
		m_pGameState_->OnEnter();
	}
}
