#include "stdafx.h"
#include "game/GamePlayState.h"
#include "extlib/rapidjson/document.h"
#include "util/JsonTools.h"
#include "services/GraphicService.h"
#include "Engine.h"

GamePlayState::GamePlayState()/*: m_hero_(nullptr)*/ {
}

void GamePlayState::OnEnter() {
//	m_hero_ = new Hero();
	m_tileSet_.LoadTileType();
	LoadMap();
}

void GamePlayState::OnExit() {
}

void GamePlayState::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	pGraphicService->DrawTestWhiteBackGround();
	m_tileSet_.Render(dt);
}

void GamePlayState::Update(float dt) {
}

bool GamePlayState::LoadMap() {
	Document d;
	// TODO: 添加数据有效性判断
	if (LoadJsonFile(d, "content/stages/map-test1.json")) {
		auto tileArray = d["room"][0]["tile"].GetArray();
		for(auto& tile: tileArray) {
			m_tileSet_.AddTile(tile[0].GetInt(), tile[1].GetInt(), tile[2].GetInt());
		}
		return true;
	}
	return false;
}

