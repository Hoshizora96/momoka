#include "stdafx.h"
#include "Engine.h"
#include "objects/Hero.h"
#include "services/GraphicService.h"
#include "fsm/HeroState.h"
#include "fsm/hero/StandState.h"
#include "services/InputService.h"
#include "util/JsonTools.h"

//Hero::Hero() : m_defaultHorizontalVelocity_(400.f), m_state_(new StandState(*this)), m_jumpnumber_(0) {
//	SecureZeroMemory(&m_physicalBody_, sizeof(PhysicalBody));
//	SecureZeroMemory(&m_nextFramePhysicalBody_, sizeof(PhysicalBody));
//
//	m_physicalBody_.collisionWidth = 1 * momoka_global::TILE_SIZE;
//	m_physicalBody_.collisionHeight = 2 * momoka_global::TILE_SIZE;
//}
//
//Hero::~Hero() {
//}
//
void Hero::Render(float dt) {
	const auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	float x = physicalBody.GetPosition().GetX() + physicalBody.GetVelocity().GetX() * (dt / 1000);
	float y = physicalBody.GetPosition().GetY() + physicalBody.GetVelocity().GetY() * (dt / 1000);

	pGraphicService->DrawRect(x, y, momoka_global::TILE_SIZE, momoka_global::TILE_SIZE * 2);

}


bool Hero::SwitchState(HeroState* state) {
	if (state != nullptr) {
		SafeDelete(&m_state_);
		m_state_ = state;
		return true;
	}
	return false;
}

void Hero::HandleCollisionInfo(CollisionInfo info) {
	// 这里是默认情况，要想定制新的情况就修改这里的函数
	if (info.isOnGround) {
		SwitchState(m_state_->Onland());
	}
	physicalBody.SetPosition(info.correctedX, info.correctedY);
	physicalBody.SetVelocity(info.correctedVelocityX, info.correctedVelocityY);
}

bool Hero::LoadConfig(char* path) {
	rapidjson::Document d;
	// "content/tiles/tile-type-test.json"
	if (LoadJsonFile(d, path)) {
		physicalBody.SetDefaultHorizonalVelocity(d["defaultHorizonalVelocity"].GetFloat());
		return true;
	}
	return false;
}

void Hero::HandleInput() {
	const auto pInputService = Engine::m_serviceLoader.LocateService<InputService>(SERVICE_TYPE::Service_input).
	                                                   lock();

	if (pInputService->IsKeyEventHappened(DIK_A, Key_down)) {
		SwitchState(m_state_->LeftKeyState(Key_down));
	}
	if (pInputService->IsKeyEventHappened(DIK_A, Key_release)) {
		SwitchState(m_state_->LeftKeyState(Key_release));
	}

	if (pInputService->IsKeyEventHappened(DIK_D, Key_down)) {
		SwitchState(m_state_->RightKeyState(Key_down));
	}
	if (pInputService->IsKeyEventHappened(DIK_D, Key_release)) {
		SwitchState(m_state_->RightKeyState(Key_release));
	}

	if (pInputService->IsKeyEventHappened(DIK_K, Key_press)) {
		SwitchState(m_state_->JumpKeyState(Key_press));
	}
	if (pInputService->IsKeyEventHappened(DIK_K, Key_release)) {
		SwitchState(m_state_->JumpKeyState(Key_release));
	}
}


Hero::~Hero() {
}

Hero::Hero(World& world): Entity(), m_state_(nullptr), m_jumpnumber_(0), m_world_(world) {
	m_state_ = new StandState(*this);
	physicalBody.SetVelocity(0, 0);
	physicalBody.SetBodySize(momoka_global::TILE_SIZE, momoka_global::TILE_SIZE * 2);
	physicalBody.SetPosition(0, 0);
}

int Hero::GetJumpNum() const {
	return this->m_jumpnumber_;
}

void Hero::SetJumpNum(int num) {
	m_jumpnumber_ = num;
}

void Hero::Update(float dt) {
	HandleInput();

	auto velocity = physicalBody.GetVelocity();
	auto position = physicalBody.GetPosition();
	physicalBody.SetPosition(position.GetX() + velocity.GetX() * dt, position.GetY() + velocity.GetY() * dt);

	//	m_physicalBody_=m_nextFramePhysicalBody_;

	SwitchState(m_state_->Update(dt));

	auto info = m_world_.GetCollisionDetector().CheckTileCollision(physicalBody);
	HandleCollisionInfo(info);


	//	if (m_pCollisionDetector_ != nullptr) {
	//		auto tileCollisionVector = m_pCollisionDetector_->TileCollisionChecker(m_physicalBody_);
	//		// 如果你想针对不同的tile做出不同的行为，就在这个for循环中添加吧
	//		for (auto tileCollision : tileCollisionVector) {
	//			m_physicalBody_ = m_pCollisionDetector_->TileCollisionDefaultSolver(tileCollision, m_physicalBody_);
	//
	//			switch (tileCollision.flag) {
	//			case Collision_down:
	//				SwitchState(m_state_->Onland());
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}

	//		if (m_pCollisionDetector_ != nullptr) {
	//			m_nextFramePhysicalBody_ = m_physicalBody_;
	//			m_nextFramePhysicalBody_.posX += m_physicalBody_.velocityX * dt;
	//			m_nextFramePhysicalBody_.posY += m_physicalBody_.velocityY * dt;
	//			auto tileCollisionVector = m_pCollisionDetector_->TileCollisionChecker(m_nextFramePhysicalBody_);
	//			for (auto tileCollision : tileCollisionVector) {
	//				m_nextFramePhysicalBody_ = m_pCollisionDetector_->TileCollisionDefaultSolver(tileCollision, m_nextFramePhysicalBody_);
	//			}
	//		}
}
