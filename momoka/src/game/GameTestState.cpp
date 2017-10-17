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
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(momoka_global::SERVICE_TYPE::Service_graphic).lock();
	pGraphicService->DrawTestWhiteBackGround();
	for (auto tile : m_tiles_) {
		int y = tile.first % 1000000;
		int x = (tile.first - y) / 1000000;
		auto type = tile.second;
		auto tileInfo = m_tileInfoMap_[type];
		pGraphicService->DrawRect(x * momoka_global::TILE_SIZE, y * momoka_global::TILE_SIZE, tileInfo.width, tileInfo.height);
	}
	m_pPlayerCharacter_->Render(dt);
}

void GameTestState::Update() {

	EntityInit(m_pPlayerCharacter_);

	// 在这里我尝试了一下命令模式
	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(momoka_global::SERVICE_TYPE::Service_input).lock();


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

	if(pInputService->IsKeyPressed(DIK_K)) {
		m_pPlayerCharacter_->Jump();
	}

	GlobalPhysicsSimulation(m_pPlayerCharacter_);
	m_pPlayerCharacter_->Update();
}

void GameTestState::WorldLoader() {
	TileInfo normalTile;
	normalTile.width = momoka_global::TILE_SIZE;
	normalTile.height = momoka_global::TILE_SIZE;
	normalTile.friction = 1;

	m_tileInfoMap_.insert(std::make_pair(0, normalTile));

	m_pPlayerCharacter_->SetX(momoka_global::TILE_SIZE);
	m_pPlayerCharacter_->SetY(momoka_global::TILE_SIZE);

	// Tile坐标存在一个__int64数里面，因为unordered_map的key不支持结构体

	int y = 10;
	for(int x = 0; x < 21; x++) {
		m_tiles_[TileMapKeyConvert(x, y)] = 0;
	}
	
}

void GameTestState::GlobalPhysicsSimulation(Entity* entity) {
	// 这里用来做全局物理模拟，主要是重力模拟与Tile碰撞检测
	// TODO: 这里面重复的东西太多了，尽量整合一下，把重复的部分抽出来新建函数

	const auto defaultTileInfo = GetDefaultTileInfo();
	entity->ClearObstructFlags();

	auto x = entity->GetX();
	auto y = entity->GetY();

	auto vx = entity->GetVelocityX();
	auto vy = entity->GetVelocityY();

	// 防止埋到墙里
	if (vx < 0) x -= 0.1;
	//	else x += 0.1;
	if (vy < 0) y -= 0.1;
	//	else y += 0.1;

	// 到左边界
	if (x <= 0 && entity->GetVelocityX() < 0) {
		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_left, defaultTileInfo);
		entity->SetX(0);
	}

	// 到上边界
	if (y <= 0 && entity->GetVelocityY() < 0) {
		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_up, defaultTileInfo);
		entity->SetY(0);
	}

	float entityWidth = entity->GetCollisionWidth();
	float entityHeight = entity->GetCollisionHeight();
	// 规定矩形左上角为起始点（start），右下角为终止点（end）
	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
	__int64 xEndTile = int((x + entityWidth) / momoka_global::TILE_SIZE);
	__int64 yEndTile = int((y + entityHeight) / momoka_global::TILE_SIZE);

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
			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_left, defaultTileInfo)) {
					m_pPlayerCharacter_->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
				}
			}
			else {
				if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_up, defaultTileInfo)) {
					m_pPlayerCharacter_->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
				}
			}
		}
		else if (vx < 0) {
			if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_left, defaultTileInfo)) {
				m_pPlayerCharacter_->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
			}
		}
		else if (vy < 0) {
			if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_up, defaultTileInfo)) {
				m_pPlayerCharacter_->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
			}
		}
	}

	if (leftDownItem != nullItem) {
		if (vx < 0 && vy > 0) {
			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
			float dy = (y + entityHeight) - yEndTile * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_left, defaultTileInfo)) {
					entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
				}
			}
			else {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_down, defaultTileInfo)) {
					entity->SetY((yEndTile) * momoka_global::TILE_SIZE - entityHeight);
					entity->Onland();
				}
			}
		}
		else if (vx < 0) {
			if ((y + entityHeight) - int(y + entityHeight) != 0) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_left, defaultTileInfo)) {
					entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
				}
			}
		}
		else if (vy > 0) {

			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_down, defaultTileInfo)) {
				entity->SetY((yEndTile) * momoka_global::TILE_SIZE - entityHeight);
				entity->Onland();
			}

		}
	}

	if (rightUpItem != nullItem) {
		if (vx > 0 && vy < 0) {
			float dx = x + entityWidth - xEndTile * momoka_global::TILE_SIZE;
			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_right, defaultTileInfo)) {
					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
				}
			}
			else {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_up, defaultTileInfo)) {
					entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
				}
			}
		}
		else if (vx > 0) {
			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_right, defaultTileInfo)) {
				entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
			}
		}
		else if (vy < 0) {
			if ((x + entityWidth) - int(x + entityWidth) != 0) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_up, defaultTileInfo)) {
					entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
				}
			}
		}
	}

	if (rightDownItem != nullItem) {
		if (vx > 0 && vy > 0) {
			float dx = x + entityWidth - xEndTile * momoka_global::TILE_SIZE;
			float dy = y + entityHeight - yEndTile * momoka_global::TILE_SIZE;
			if (abs(vy / vx) <= abs(dy / dx)) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_right, defaultTileInfo)) {
					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
				}
			}
			else {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_down, defaultTileInfo)) {
					entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
					entity->Onland();
				}
			}
		}
		else if (vx > 0) {
			if ((y + entityHeight) - int(y + entityHeight) != 0) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_right, defaultTileInfo)) {
					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
				}
			}
		}
		else if (vy > 0) {
			if ((x + entityWidth) - int(x + entityWidth) != 0) {
				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_down, defaultTileInfo)) {
					entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
					entity->Onland();
				}
			}
		}
	}

	for (int i = xStartTile + 1; i < xEndTile; i++) {
		auto key = TileMapKeyConvert(i, yStartTile);
		auto item = m_tiles_.find(key);
		if (item != nullItem) {
			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_up, defaultTileInfo)) {
				entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
			}
			break;
		}

		key = TileMapKeyConvert(i, yEndTile);
		item = m_tiles_.find(key);
		if (item != nullItem) {
			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_down, defaultTileInfo)) {
				entity->SetY(yEndTile* momoka_global::TILE_SIZE - entityHeight);
				entity->Onland();
			}
			break;
		}
	}

	for (int i = yStartTile + 1; i < yEndTile; i++) {
		auto key = TileMapKeyConvert(xStartTile, i);
		auto item = m_tiles_.find(key);
		if (item != nullItem) {
			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_left, defaultTileInfo)) {
				entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
			}
			break;
		}

		key = TileMapKeyConvert(xEndTile, i);
		item = m_tiles_.find(key);
		if (item != nullItem) {
			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAG::Collision_right, defaultTileInfo)) {
				entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
			}
			break;
		}
	}

}

void GameTestState::EntityInit(Entity* entity) {
	// TODO: 这里面除了将entity速度设为0，还做了着陆判断，把这两个功能分开

//	entity->SetVelocityX(0);
//	entity->SetVelocityY(0);
//
//	auto x = entity->GetX();
//	auto y = entity->GetY();
//
//	float entityWidth = entity->GetCollisionWidth();
//	float entityHeight = entity->GetCollisionHeight();
//	// 规定矩形左上角为起始点（start），右下角为终止点（end）
//	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
//	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
//	__int64 xEndTile = int((x + entityWidth) / momoka_global::TILE_SIZE);
//	__int64 yEndTile = int((y + entityHeight) / momoka_global::TILE_SIZE);
//
//	auto nullItem = m_tiles_.end();
//
//	for (int i = xStartTile; i <= xEndTile; i++) {
//		auto key = TileMapKeyConvert(i, yEndTile);
//		auto item = m_tiles_.find(key);
//		if (item != nullItem) {
//			entity->Onland();
//			break;
//		}
//	}
}

long long GameTestState::TileMapKeyConvert(long long xTile, long long yTile) {
	return xTile * momoka_global::MULX + yTile;
}
