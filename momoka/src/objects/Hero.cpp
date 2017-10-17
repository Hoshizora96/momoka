#include "stdafx.h"
#include "Engine.h"
#include "objects/Hero.h"
#include "services/GraphicService.h"
#include "fsm/hero/StandState.h"


Hero::Hero(): m_movingVelocity_(250.f), m_state_(new StandState(*this)) {
	m_velocityX_ = 0;
	m_velocityY_ = 0;
	m_collisionWidth_ = 1 * momoka_global::TILE_SIZE;
	m_collisionHeight_ = 2 * momoka_global::TILE_SIZE;
}

Hero::~Hero() {
}

void Hero::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(momoka_global::SERVICE_TYPE::Service_graphic).lock();
	float x = m_posX_ + m_velocityX_ * (dt / 1000);
	float y = m_posY_ + m_velocityY_ * (dt / 1000);
	pGraphicService->DrawRect(x, y, momoka_global::TILE_SIZE, momoka_global::TILE_SIZE*2);

}

void Hero::MoveLeft() {
	m_velocityX_ = -m_movingVelocity_;
}

void Hero::MoveRight() {
	m_velocityX_ = m_movingVelocity_;
}

void Hero::MoveUp() {
	m_velocityY_ = -m_movingVelocity_;
}

void Hero::MoveDown() {
	m_velocityY_ = m_movingVelocity_;
}

void Hero::Jump() {
	SwitchState(m_state_->JumpKeyDown());
}


bool Hero::SwitchState(HeroState* state) {
	if(state != nullptr) {
		SafeDelete(&m_state_);
		m_state_ = state;
		return true;
	}
	return false;
}

void Hero::Onland() {
	SwitchState(m_state_->Onland());
}

void Hero::Update() {
	SwitchState(m_state_->Update());
	m_posX_ += m_velocityX_ * (1 / Engine::m_refreshRate);
	m_posY_ += m_velocityY_ * (1 / Engine::m_refreshRate);
}
