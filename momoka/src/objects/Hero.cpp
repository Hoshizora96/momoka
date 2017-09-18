#include "stdafx.h"
#include "Engine.h"
#include "objects/Hero.h"
#include "services/GraphicService.h"


Hero::Hero(): m_movingVelocity_(250.f) {
	m_velocityX_ = 0;
	m_velocityY_ = 0;
}

Hero::~Hero() {
}

void Hero::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(SERVICE_TYPE::graphicService).lock();
	float x = m_posX_ + m_velocityX_ * (dt / 1000);
	float y = m_posY_ + m_velocityY_ * (dt / 1000);
	pGraphicService->DrawRect(x, y, 50, 50);
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

void Hero::Update() {
	m_posX_ += m_velocityX_ * (1 / Engine::m_refreshRate);
	m_posY_ += m_velocityY_ * (1 / Engine::m_refreshRate);
}
