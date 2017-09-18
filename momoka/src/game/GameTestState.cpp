#include "stdafx.h"
#include "services/GraphicService.h"
#include "game/GameTestState.h"
#include "Engine.h"
#include "objects/Entity.h"
#include "objects/Hero.h"
#include "commands/Command.h"
#include "commands/actor/MoveDownCommand.h"
#include "commands/actor/MoveLeftCommand.h"
#include "commands/actor/MoveRightCommand.h"
#include "commands/actor/MoveUpCommand.h"
#include "services/InputService.h"


GameTestState::GameTestState(): m_pPlayerCharacter_(nullptr), m_commandW_(nullptr), m_commandA_(nullptr),
                                m_commandS_(nullptr), m_commandD_(nullptr) {
}

GameTestState::~GameTestState() {
}

void GameTestState::OnEnter() {
	m_pPlayerCharacter_ = new Hero();
	m_commandW_ = new MoveUpCommand(m_pPlayerCharacter_);
	m_commandA_ = new MoveLeftCommand(m_pPlayerCharacter_);
	m_commandS_ = new MoveDownCommand(m_pPlayerCharacter_);
	m_commandD_ = new MoveRightCommand(m_pPlayerCharacter_);
	WorldLoader();
}

void GameTestState::OnExit() {
	SafeDelete(&m_pPlayerCharacter_);
}

void GameTestState::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(SERVICE_TYPE::graphicService).lock();
	for (auto tile : m_tiles_) {
		const auto tileInfo = m_tileInfoMap_.find(tile.m_type_)->second;
		pGraphicService->DrawRect(tile.m_posX_, tile.m_posY_, tileInfo.m_width, tileInfo.m_height);
	}
	m_pPlayerCharacter_->Render(dt);
}

void GameTestState::Update() {

	// 在这里我尝试了一下命令模式
	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(SERVICE_TYPE::inputService).lock();


	if(pInputService->IsKeyPressed(DIK_W)) {
		m_commandW_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_S)) {
		m_commandS_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_A)) {
		m_commandA_->Execute();
	}

	if (pInputService->IsKeyPressed(DIK_D)) {
		m_commandD_->Execute();
	}

	m_pPlayerCharacter_->Update();
}

void GameTestState::WorldLoader() {
	TileInfo normalTile(50, 0, 50);

	m_tileInfoMap_.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter_->SetX(50);
	m_pPlayerCharacter_->SetY(50);

	const Tile tile(0, 100, 100);
	m_tiles_.push_back(tile);
}
