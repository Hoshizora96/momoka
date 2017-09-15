#pragma once
#include "stdafx.h"
#include "services/GraphicService.h"
#include "game/GameTestState.h"
#include "Engine.h"
#include "commands/Command.h"
#include "commands/actor/MoveDownCommand.h"
#include "commands/actor/MoveLeftCommand.h"
#include "commands/actor/MoveRightCommand.h"
#include "commands/actor/MoveUpCommand.h"
#include "services/InputService.h"

GameTestState::GameTestState(ServiceLoader& serviceLoader): m_pPlayerCharacter(nullptr) {
}

GameTestState::~GameTestState() {
}

void GameTestState::OnEnter() {
	m_pPlayerCharacter = new Hero();
}

void GameTestState::OnExit() {
	SafeDelete(&m_pPlayerCharacter);
}

void GameTestState::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(SERVICE_TYPE::graphicService).lock();
	for (auto tile : m_tiles) {
		const auto tileInfo = m_tileInfoMap.find(tile.m_type_)->second;
		pGraphicService->DrawRect(tile.m_posX_, tile.m_posY_, tileInfo.m_width, tileInfo.m_height);
	}

	float x = m_pPlayerCharacter->GetX() + m_pPlayerCharacter->GetVelocityX() * (dt / 1000);
	float y = m_pPlayerCharacter->GetY() + m_pPlayerCharacter->GetVelocityY() * (dt / 1000);
	pGraphicService->DrawRect(x, y, x + 50, y + 50);
}

void GameTestState::Update() {
	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(SERVICE_TYPE::inputService).lock();

	Command command_W = static_cast<Command>(MoveUpCommand(m_pPlayerCharacter));
	Command command_S = static_cast<Command>(MoveDownCommand(m_pPlayerCharacter));
	Command command_A = static_cast<Command>(MoveLeftCommand(m_pPlayerCharacter));
	Command command_D = static_cast<Command>(MoveRightCommand(m_pPlayerCharacter));


	if(pInputService->IsKeyPressed(DIK_W)) {
		command_W.Execute();
	}

	if (pInputService->IsKeyPressed(DIK_S)) {
		command_S.Execute();
	}

	if (pInputService->IsKeyPressed(DIK_A)) {
		command_A.Execute();
	}

	if (pInputService->IsKeyPressed(DIK_D)) {
		command_D.Execute();
	}

	
}

void GameTestState::WorldLoader() {
	TileInfo normalTile(50, 0, 50);

	m_tileInfoMap.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter->SetX(50);
	m_pPlayerCharacter->SetY(50);

	const Tile tile(0, 100, 100);
	m_tiles.push_back(tile);
}
