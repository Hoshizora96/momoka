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
	pGraphicService->DrawTestWhiteBackGround();
	for (auto tile : m_tiles_) {
		int y = tile.first % 1000000;
		int x = (tile.first - y) / 1000000;
		auto type = tile.second;
		auto tileInfo = m_tileInfoMap_[type];
		pGraphicService->DrawRect(x * TILE_SIZE, y * TILE_SIZE, tileInfo.width, tileInfo.height);
	}
	m_pPlayerCharacter_->Render(dt);
}

void GameTestState::Update() {

	// 在这里我尝试了一下命令模式
	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(SERVICE_TYPE::inputService).lock();


	if (pInputService->IsKeyPressed(DIK_W)) {
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

	GlobalPhysicsSimulation(m_pPlayerCharacter_);
	m_pPlayerCharacter_->Update();
}

void GameTestState::WorldLoader() {
	TileInfo normalTile;
	normalTile.width = TILE_SIZE;
	normalTile.height = TILE_SIZE;
	normalTile.friction = 1;

	m_tileInfoMap_.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter_->SetX(TILE_SIZE);
	m_pPlayerCharacter_->SetY(TILE_SIZE);

	// Tile坐标存在一个__int64数里面，因为unordered_map的key不支持结构体
	int x = 5;
	int y = 3;
	m_tiles_[TileMapKeyConvert(x, y)] = 0;
}

void GameTestState::GlobalPhysicsSimulation(Entity* entity) {
	// 这里用来做全局物理模拟，主要是重力模拟与Tile碰撞检测
	const auto defaultTileInfo = GetDefaultTileInfo();
	entity->ClearObstructFlags();

	auto x = entity->GetX();
	auto y = entity->GetY();

	auto vx = m_pPlayerCharacter_->GetVelocityX();
	auto vy = m_pPlayerCharacter_->GetVelocityY();

	if (vx < 0) x -= 0.1;
	//	else x += 0.1;
	if (vy < 0) y -= 0.1;
	//	else y += 0.1;

	if (x <= 0 && entity->GetVelocityX() < 0) {
		m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::left, defaultTileInfo);
		entity->SetX(0);
	}

	if (y <= 0 && entity->GetVelocityY() < 0) {
		m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::up, defaultTileInfo);
		entity->SetY(0);
	}

	float entityWidth = entity->GetCollisionWidth();
	float entityHeight = entity->GetCollisionHeight();
	// 规定矩形左上角为起始点（start），右下角为终止点（end）
	__int64 xStartTile = int(x / TILE_SIZE);
	__int64 yStartTile = int(y / TILE_SIZE);
	__int64 xEndTile = int((x + entityWidth) / TILE_SIZE);
	__int64 yEndTile = int((y + entityHeight) / TILE_SIZE);

	__int64 leftUpTileKey = TileMapKeyConvert(xStartTile, yStartTile);
	__int64 leftDownTileKey = TileMapKeyConvert(xStartTile, yEndTile);
	__int64 rightUpTileKey = TileMapKeyConvert(xEndTile, yStartTile);
	__int64 rightDownTileKey = TileMapKeyConvert(xEndTile, yEndTile);

	auto leftUpItem = m_tiles_.find(leftUpTileKey);
	auto leftDownItem = m_tiles_.find(leftDownTileKey);
	auto rightUpItem = m_tiles_.find(rightUpTileKey);
	auto rightDownItem = m_tiles_.find(rightDownTileKey);

	auto nullItem = m_tiles_.end();

	if (leftUpItem != nullItem) {
		if (vx < 0 && vy < 0) {
			float dx = x - (xStartTile + 1) * TILE_SIZE;
			float dy = y - (yStartTile + 1) * TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::left, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX((xStartTile + 1) * TILE_SIZE);
				}
			}
			else {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::up, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY((yStartTile + 1) * TILE_SIZE);
				}
			}
		}
		else if (vx < 0) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::left, defaultTileInfo)) {
				m_pPlayerCharacter_->SetX((xStartTile + 1) * TILE_SIZE);
			}
		}
		else if (vy < 0) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::up, defaultTileInfo)) {
				m_pPlayerCharacter_->SetY((yStartTile + 1) * TILE_SIZE);
			}
		}
	}

	if (leftDownItem != nullItem) {
		if (vx < 0 && vy > 0) {
			float dx = x - (xStartTile + 1) * TILE_SIZE;
			float dy = (y + entityHeight) - yEndTile * TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::left, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX((xStartTile + 1) * TILE_SIZE);
				}
			}
			else {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::down, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY((yEndTile) * TILE_SIZE - entityHeight);
				}
			}
		}
		else if (vx < 0) {
			if ((y + entityHeight) - int(y + entityHeight) != 0) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::left, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX((xStartTile + 1) * TILE_SIZE);
				}
			}
		}
		else if (vy > 0) {

			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::down, defaultTileInfo)) {
				m_pPlayerCharacter_->SetY((yEndTile) * TILE_SIZE - entityHeight);
			}

		}
	}

	if (rightUpItem != nullItem) {
		if (vx > 0 && vy < 0) {
			float dx = x + entityWidth - xEndTile * TILE_SIZE;
			float dy = y - (yStartTile + 1) * TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::right, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX(xEndTile * TILE_SIZE - entityWidth);
				}
			}
			else {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::up, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY((yStartTile + 1) * TILE_SIZE);
				}
			}
		}
		else if (vx > 0) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::right, defaultTileInfo)) {
				m_pPlayerCharacter_->SetX(xEndTile * TILE_SIZE - entityWidth);
			}
		}
		else if (vy < 0) {
			if ((x + entityWidth) - int(x + entityWidth) != 0) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::up, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY((yStartTile + 1) * TILE_SIZE);
				}
			}
		}
	}

	if (rightDownItem != nullItem) {
		if (vx > 0 && vy > 0) {
			float dx = x + entityWidth - xEndTile * TILE_SIZE;
			float dy = y + entityHeight - yEndTile * TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::right, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX(xEndTile * TILE_SIZE - entityWidth);
				}
			}
			else {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::down, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY(yEndTile * TILE_SIZE - entityHeight);
				}
			}
		}
		else if (vx > 0) {
			if ((y + entityHeight) - int(y + entityHeight) != 0) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::right, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX(xEndTile * TILE_SIZE - entityWidth);
				}
			}
		}
		else if (vy > 0) {
			if ((x + entityWidth) - int(x + entityWidth) != 0) {
				if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::down, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY(yEndTile * TILE_SIZE - entityHeight);
				}
			}
		}
	}

	for (int i = xStartTile + 1; i < xEndTile; i++) {
		auto key = TileMapKeyConvert(i, yStartTile);
		auto item = m_tiles_.find(key);
		if (item != nullItem) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::up, defaultTileInfo)) {
				m_pPlayerCharacter_->SetY((yStartTile + 1) * TILE_SIZE);
			}
			break;
		}

		key = TileMapKeyConvert(i, yEndTile);
		item = m_tiles_.find(key);
		if (item != nullItem) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::down, defaultTileInfo)) {
				m_pPlayerCharacter_->SetY(yEndTile* TILE_SIZE - entityHeight);
			}
			break;
		}
	}

	for (int i = yStartTile + 1; i < yEndTile; i++) {
		auto key = TileMapKeyConvert(xStartTile, i);
		auto item = m_tiles_.find(key);
		if (item != nullItem) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::left, defaultTileInfo)) {
				m_pPlayerCharacter_->SetX((xStartTile + 1) * TILE_SIZE);
			}
			break;
		}

		key = TileMapKeyConvert(xEndTile, i);
		item = m_tiles_.find(key);
		if (item != nullItem) {
			if (m_pPlayerCharacter_->TakeTileCollision(COLLISION_FLAG::right, defaultTileInfo)) {
				m_pPlayerCharacter_->SetX(xEndTile * TILE_SIZE - entityWidth);
			}
			break;
		}
	}

}

long long GameTestState::TileMapKeyConvert(long long xTile, long long yTile) {
	return xTile * MULX + yTile;
}
