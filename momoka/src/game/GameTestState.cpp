#pragma once
#include "stdafx.h"
#include "game/GameTestState.h"

GameTestState::GameTestState(ServiceLoader& serviceLoader) {
}

GameTestState::~GameTestState() {
}

void GameTestState::OnEnter() {
	m_pPlayerCharacter = new Hero();
}

void GameTestState::OnExit() {
}

void GameTestState::Render(float dt) {
	for(auto tile : m_tiles) {
		
	}
}

void GameTestState::Update() {
}

void GameTestState::WorldLoader() {
	TileInfo normalTile;
	normalTile.m_friction = 0;
	normalTile.m_height = 50;
	normalTile.m_width = 50;

	m_tileInfoMap.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter->SetX(50);
	m_pPlayerCharacter->SetY(50);

	const Tile tile(0, 100, 100);
	m_tiles.push_back(tile);
}
