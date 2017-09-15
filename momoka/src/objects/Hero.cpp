#pragma once
#include "Engine.h"
#include "stdafx.h"
#include "objects/Hero.h"


inline Hero::Hero(): m_movingVelocity_(10.f) {
}

Hero::~Hero() {
}

bool Hero::Render(float dt) {
}

bool Hero::MoveLeft() {
	m_velocityX_ = -m_movingVelocity_;
}

bool Hero::MoveRight() {
	m_velocityX_ = m_movingVelocity_;
}

bool Hero::MoveUp() {
	m_velocityY_ = -m_movingVelocity_;
}

bool Hero::MoveDown() {
	m_velocityY_ = m_movingVelocity_;
}

bool Hero::Update() {
	m_posX_ = m_velocityX_ * (1 / Engine::m_refreshRate);
	m_posY_ = m_velocityY_ * (1 / Engine::m_refreshRate);
	return true;
}
