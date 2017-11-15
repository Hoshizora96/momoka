#include "stdafx.h"
#include "game/GameController.h"
#include "game/GamePlayState.h"

GameController::GameController(): m_pGameState_(nullptr) {
}

GameController::~GameController() {
}

void GameController::Update(float dt) {
	m_pGameState_->Update(dt);
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
		m_pGameState_ = new GamePlayState();
		m_pGameState_->OnEnter();
	}
}
