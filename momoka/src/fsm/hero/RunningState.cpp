#include "stdafx.h"
#include "fsm/hero/RunningState.h"
#include "fsm/hero/FallingState.h"
#include "fsm/hero/JumpState.h"
#include "fsm/hero/StandState.h"

RunningState::RunningState(Hero& hero, bool isMoveLeft)
	: HeroState(hero), m_isLeftKeyDown_(false), m_isRightKeyDown_(false), m_isJumpKeyDown_(false), m_isOnland_(true) {
	if(isMoveLeft) {
		m_isLeftKeyDown_ = true;
		m_hero_.SetVelocityX(-m_hero_.GetDefaultHorizontalVelocity());
	}
	else {
		m_isRightKeyDown_ = true;
		m_hero_.SetVelocityX(m_hero_.GetDefaultHorizontalVelocity());
	}
}

RunningState::~RunningState() {
}

HeroState* RunningState::LeftKeyDown() {
	m_isLeftKeyDown_ = true;
	m_hero_.SetVelocityX(-m_hero_.GetDefaultHorizontalVelocity());
	return nullptr;
}

HeroState* RunningState::RightKeyDown() {
	m_isRightKeyDown_ = true;
	m_hero_.SetVelocityX(m_hero_.GetDefaultHorizontalVelocity());
	return nullptr;
}

HeroState* RunningState::JumpKeyDown() {
	return new JumpState(m_hero_);
}

HeroState* RunningState::Onland() {
	m_isOnland_ = true;
	return nullptr;
}

HeroState* RunningState::Update() {
	if (!m_isOnland_) return new FallingState(m_hero_);
	if (!m_isRightKeyDown_ && !m_isLeftKeyDown_) return new StandState(m_hero_);

	m_isOnland_ = false;
	m_isRightKeyDown_ = false;
	m_isLeftKeyDown_ = false;
	return nullptr;
}
