#include "stdafx.h"
#include "services/GraphicService.h"
#include "game/GameTestState.h"
#include "Engine.h"
#include "objects/Entity.h"
#include "objects/Hero.h"
#include "services/InputService.h"
#include "util/Log.h"


GameTestState::GameTestState() : m_collisionDetector_(m_tilesMap_, m_tileTypeMap_),
                                 m_pPlayerCharacter_(nullptr) {
	MOMOKA_LOG(momoka::info) << "GameTestState Initialized";
}

GameTestState::~GameTestState() {
}

void GameTestState::OnEnter() {
	m_pPlayerCharacter_ = new Hero();
	WorldLoader();
}

void GameTestState::OnExit() {
	SafeDelete(&m_pPlayerCharacter_);
}

void GameTestState::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	pGraphicService->DrawTestWhiteBackGround();
	for (auto tile : m_tilesMap_) {
		int y = tile.first % 1000000;
		int x = (tile.first - y) / 1000000;
		auto type = tile.second;
		auto tileInfo = m_tileTypeMap_[type];
		pGraphicService->DrawRect(x * momoka_global::TILE_SIZE, y * momoka_global::TILE_SIZE, tileInfo.width,
		                          tileInfo.height);
	}
	m_pPlayerCharacter_->Render(dt);
}

void GameTestState::Update() {

	//	// 在这里我尝试了一下命令模式
	//	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(momoka_global::SERVICE_TYPE::Service_input).
	//	                                             lock();
	//
	//
	//	if (pInputService->IsKeyEventHappened(DIK_W)) {
	//		m_commandW_->Execute();
	//	}
	//
	//	if (pInputService->IsKeyEventHappened(DIK_S)) {
	//		m_commandS_->Execute();
	//	}
	//
	//	if (pInputService->IsKeyEventHappened(DIK_A)) {
	//		m_commandA_->Execute();
	//	}
	//
	//	if (pInputService->IsKeyEventHappened(DIK_D)) {
	//		m_commandD_->Execute();
	//	}
	//
	//	if (pInputService->IsKeyEventHappened(DIK_K, Key_press)) {
	//		m_pPlayerCharacter_->Jump();
	//	}

	//GlobalPhysicsSimulation(m_pPlayerCharacter_);
	m_pPlayerCharacter_->Update();
}

void GameTestState::WorldLoader() {
	TileType normalTile;
	normalTile.width = momoka_global::TILE_SIZE;
	normalTile.height = momoka_global::TILE_SIZE;
	normalTile.friction = 1;

	m_tileTypeMap_.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter_->SetX(momoka_global::TILE_SIZE);
	m_pPlayerCharacter_->SetY(momoka_global::TILE_SIZE);
	m_pPlayerCharacter_->SetCollisionDetector(&m_collisionDetector_);

	// Tile坐标存在一个__int64数里面，因为map的key不支持结构体

	int y = 10;
	for (int x = 0; x < 20; x++) {
		m_tilesMap_[TileMapKeyConvert(x, y)] = 0;
	}

	m_tilesMap_[TileMapKeyConvert(6, 8)] = 0;
	m_tilesMap_[TileMapKeyConvert(8, 6)] = 0;
	m_tilesMap_[TileMapKeyConvert(10, 4)] = 0;

}
