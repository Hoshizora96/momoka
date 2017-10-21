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
#include "util/Log.h"


GameTestState::GameTestState(): m_pPlayerCharacter_(nullptr), m_commandW_(nullptr), m_commandA_(nullptr),
                                m_commandS_(nullptr), m_commandD_(nullptr),
                                m_collisionDetector_(m_tilesMap_, m_tileTypeMap_) {
	MOMOKA_LOG(momoka::info) << "GameTestState Initialized";
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
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		momoka_global::SERVICE_TYPE::Service_graphic).lock();
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

	// 在这里我尝试了一下命令模式
	auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(momoka_global::SERVICE_TYPE::Service_input).
	                                             lock();


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

	if (pInputService->IsKeyPressed(DIK_K)) {
		m_pPlayerCharacter_->Jump();
	}

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
	for (int x = 0; x < 21; x++) {
		m_tilesMap_[TileMapKeyConvert(x, y)] = 0;
	}

	m_tilesMap_[TileMapKeyConvert(6, 8)] = 0;
	m_tilesMap_[TileMapKeyConvert(8, 7)] = 0;

}

//void GameTestState::GlobalPhysicsSimulation(Entity* entity) {
//	// 这里用来做全局物理模拟，主要是做Entity与Tile的碰撞检测
//	// TODO: 准备移除这个函数，转而使用CollisionDetector类
//
//	/* 这里说一下碰撞检测的流程，首先求出entity碰撞矩形四个顶点坐标，查找这四个顶点所在的位置是否有tile
//	 * 如果有，说明发生了碰撞，那么就根据运动方向求出是在x或y方向上发生碰撞，从而将该方向速度分量设为0
//	 * 如果没有，就去检查四条边所在位置是否有tile，然后重复上面的流程，检查碰撞 */
//
//	const auto defaultTileInfo = GetDefaultTileInfo();
//	entity->ClearObstructFlags();
//
//	auto x = entity->GetX();
//	auto y = entity->GetY();
//
//	auto vx = entity->GetVelocityX();
//	auto vy = entity->GetVelocityY();
//
//	/* 当一个entity在左边或上边与tile相邻但未重合时，由于查找坐标所在位置对应tile时是用的整除法
//	 * （x:=40, y:=40，x/40=1, y/40=1，虽然(1,1)处没有tile，但是不知道(1,0）或(0,1)处是否有tile）
//	 * 所以检查entity左边或上边tile时不会知道与其相邻，但这种情况也属于碰撞，
//	 * 解决方法：如果entity具有向上或向左的速度分量，就在对应方向上加一个位置偏移，使其与左边或上边的tile重合，进而能够进行碰撞检测 */
//	if (vx < 0) x -= 0.1;
//	if (vy < 0) y -= 0.1;
//
//	// 触碰到地图左边界
//	if (x <= 0 && entity->GetVelocityX() < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo);
//		entity->SetX(0);
//	}
//
//	// 触碰到地图上边界
//	if (y <= 0 && entity->GetVelocityY() < 0) {
//		m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo);
//		entity->SetY(0);
//	}
//
//	float entityWidth = entity->GetCollisionWidth();
//	float entityHeight = entity->GetCollisionHeight();
//	// 规定矩形左上角为起始点（start），右下角为终止点（end）
//	__int64 xStartTile = int(x / momoka_global::TILE_SIZE);
//	__int64 yStartTile = int(y / momoka_global::TILE_SIZE);
//	__int64 xEndTile = int((x + entityWidth) / momoka_global::TILE_SIZE);
//	__int64 yEndTile = int((y + entityHeight) / momoka_global::TILE_SIZE);
//
//	__int64 leftUpTileKey = TileMapKeyConvert(xStartTile, yStartTile);
//	__int64 leftDownTileKey = TileMapKeyConvert(xStartTile, yEndTile);
//	__int64 rightUpTileKey = TileMapKeyConvert(xEndTile, yStartTile);
//	__int64 rightDownTileKey = TileMapKeyConvert(xEndTile, yEndTile);
//
//	auto leftUpItem = m_tilesMap_.find(leftUpTileKey);
//	auto leftDownItem = m_tilesMap_.find(leftDownTileKey);
//	auto rightUpItem = m_tilesMap_.find(rightUpTileKey);
//	auto rightDownItem = m_tilesMap_.find(rightDownTileKey);
//
//	auto nullItem = m_tilesMap_.end();
//
//	/* 下面四个if语句块是整个碰撞检测最复杂的一部分代码，这段代码进行四个角的碰撞检测。
//	 * 这里我通过检测合成速度斜率来计算碰撞的方向，从而决定将x或y方向速度分量设为0
//	 * 注意要考虑 vx == 0 和 vy == 0 的情况，右下边发生接触是需要考虑的特殊情况，主要是针对贴着边运动的情况 */
//
//	if (leftUpItem != nullItem) {
//		if (vx < 0 && vy < 0) {
//			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
//			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//					m_pPlayerCharacter_->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//			else {
//				if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//					m_pPlayerCharacter_->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//		else if (vx < 0) {
//			if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//				m_pPlayerCharacter_->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//		}
//		else if (vy < 0) {
//			if (m_pPlayerCharacter_->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//				m_pPlayerCharacter_->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//		}
//	}
//
//	if (leftDownItem != nullItem) {
//		if (vx < 0 && vy > 0) {
//			float dx = x - (xStartTile + 1) * momoka_global::TILE_SIZE;
//			float dy = (y + entityHeight) - yEndTile * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//					entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//			else {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//					entity->SetY((yEndTile) * momoka_global::TILE_SIZE - entityHeight);
//				}
//			}
//		}
//		else if (vy >= 0) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//				entity->SetY((yEndTile) * momoka_global::TILE_SIZE - entityHeight);
//			}
//		}
//		else if (vx < 0) {
//			if ((y + entityHeight) - int(y + entityHeight) != 0) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//					entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//	}
//
//	if (rightUpItem != nullItem) {
//		if (vx > 0 && vy < 0) {
//			float dx = x + entityWidth - xEndTile * momoka_global::TILE_SIZE;
//			float dy = y - (yStartTile + 1) * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//				}
//			}
//			else {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//					entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//		else if (vx > 0) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//				entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//			}
//		}
//		else if (vy < 0) {
//			if ((x + entityWidth) - int(x + entityWidth) != 0) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//					entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//				}
//			}
//		}
//	}
//
//	if (rightDownItem != nullItem) {
//		if (vx > 0 && vy > 0) {
//			float dx = x + entityWidth - xEndTile * momoka_global::TILE_SIZE;
//			float dy = y + entityHeight - yEndTile * momoka_global::TILE_SIZE;
//			if (abs(vy / vx) <= abs(dy / dx)) {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//					entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//				}
//			}
//			else {
//				if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//					entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//				}
//			}
//		}
//		else {
//			if (vy == 0) {
//				if ((x + entityWidth) - int(x + entityWidth) != 0) {
//					if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//						entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//					}
//				}
//			}
//			else if (vx > 0) {
//				if ((y + entityHeight) - int(y + entityHeight) != 0) {
//					if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//						entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//					}
//				}
//			}
//			else if (vy > 0) {
//				if ((x + entityWidth) - int(x + entityWidth) != 0) {
//					if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//						entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//					}
//				}
//			}
//		}
//	}
//
//	// 四条边的碰撞检测
//	for (int i = xStartTile + 1; i < xEndTile; i++) {
//		auto key = TileMapKeyConvert(i, yStartTile);
//		auto item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_up, defaultTileInfo)) {
//				entity->SetY((yStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//			break;
//		}
//
//		key = TileMapKeyConvert(i, yEndTile);
//		item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_down, defaultTileInfo)) {
//				entity->SetY(yEndTile * momoka_global::TILE_SIZE - entityHeight);
//
//			}
//			break;
//		}
//	}
//
//	for (int i = yStartTile + 1; i < yEndTile; i++) {
//		auto key = TileMapKeyConvert(xStartTile, i);
//		auto item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_left, defaultTileInfo)) {
//				entity->SetX((xStartTile + 1) * momoka_global::TILE_SIZE);
//			}
//			break;
//		}
//
//		key = TileMapKeyConvert(xEndTile, i);
//		item = m_tilesMap_.find(key);
//		if (item != nullItem) {
//			if (entity->TakeTileCollision(momoka_global::COLLISION_FLAGS::Collision_right, defaultTileInfo)) {
//				entity->SetX(xEndTile * momoka_global::TILE_SIZE - entityWidth);
//			}
//			break;
//		}
//	}
//
//}
