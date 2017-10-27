#include "stdafx.h"
#include "Engine.h"
#include "objects/Hero.h"
#include "services/GraphicService.h"
#include "fsm/hero/StandState.h"
#include "services/InputService.h"

Hero::Hero(): m_defaultHorizontalVelocity_(400.f), m_state_(new StandState(*this)) {
	SecureZeroMemory(&m_physicalBody_, sizeof(PhysicalBody));
	SecureZeroMemory(&m_nextFramePhysicalBody_, sizeof(PhysicalBody));

	m_physicalBody_.collisionWidth = 1 * momoka_global::TILE_SIZE;
	m_physicalBody_.collisionHeight = 2 * momoka_global::TILE_SIZE;
}

Hero::~Hero() {
}

void Hero::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	float x = m_physicalBody_.posX + m_physicalBody_.velocityX * (dt / 1000);
	float y = m_physicalBody_.posY + m_physicalBody_.velocityY * (dt / 1000);

	float next_x = m_nextFramePhysicalBody_.posX;
	float next_y = m_nextFramePhysicalBody_.posY;

	//		if (x > next_x && m_physicalBody_.velocityX > 0 || x < next_x && m_physicalBody_.velocityX < 0) {
	//			x = next_x;
	//		}
	//	
	//		if (y > next_y && m_physicalBody_.velocityY > 0 || y < next_y && m_physicalBody_.velocityY < 0) {
	//			y = next_y;
	//		}

	pGraphicService->DrawRect(x, y, momoka_global::TILE_SIZE, momoka_global::TILE_SIZE * 2);

}

void Hero::MoveLeft() {

}

void Hero::MoveRight() {

}

void Hero::MoveUp() {
	//	m_velocityY_ = -m_defaultHorizontalVelocity_;
}

void Hero::MoveDown() {
	//	m_velocityY_ = m_defaultHorizontalVelocity_;
}

void Hero::Jump() {

}


bool Hero::SwitchState(HeroState* state) {
	if (state != nullptr) {
		SafeDelete(&m_state_);
		m_state_ = state;
		return true;
	}
	return false;
}

void Hero::Onland() {
	SwitchState(m_state_->Onland());
}

float Hero::GetDefaultHorizontalVelocity() const {
	return m_defaultHorizontalVelocity_;
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

void Hero::Update() {
	HandleInput();
	auto dt = 1 / Engine::m_refreshRate;
	m_physicalBody_.posX += m_physicalBody_.velocityX * dt;
	m_physicalBody_.posY += m_physicalBody_.velocityY * dt;
	//	m_physicalBody_=m_nextFramePhysicalBody_;


	SwitchState(m_state_->Update());
	if (m_pCollisionDetector_ != nullptr) {
		auto tileCollisionVector = m_pCollisionDetector_->TileCollisionChecker(m_physicalBody_);
		// 如果你想针对不同的tile做出不同的行为，就在这个for循环中添加吧
		for (auto tileCollision : tileCollisionVector) {
			m_physicalBody_ = m_pCollisionDetector_->TileCollisionDefaultSolver(tileCollision, m_physicalBody_);

			switch (tileCollision.flag) {
			case Collision_down:
				SwitchState(m_state_->Onland());
				break;
			default:
				break;
			}
		}
	}

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
