#include "stdafx.h"
#include "game/GamePlayState.h"
#include "extlib/rapidjson/document.h"
#include "util/JsonTools.h"
#include "services/GraphicService.h"
#include "Engine.h"

GamePlayState::GamePlayState(): m_pWorld_(nullptr) {
	m_pWorld_ = new World();
}

void GamePlayState::OnEnter() {
	m_pWorld_->LoadConfig("no use");
}

void GamePlayState::OnExit() {
}

void GamePlayState::Render() {
	auto pGraphicService = Engine::serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	pGraphicService->DrawTestWhiteBackGround();
	m_pWorld_->Render();
}

void GamePlayState::Update(float dt) {
	m_pWorld_->Update(dt);
}

