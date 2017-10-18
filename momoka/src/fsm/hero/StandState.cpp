#include "stdafx.h"
#include "fsm/hero/StandState.h"
#include "fsm/hero/JumpState.h"
#include "fsm/hero/RunningState.h"
#include "fsm/hero/FallingState.h"

StandState::StandState(Hero& hero)
	: HeroState(hero), m_isOnland_(true) {
	m_hero_.SetVelocityX(0);
	m_hero_.SetVelocityY(0);
}

StandState::~StandState() {
}

HeroState* StandState::LeftKeyDown() {
	return new RunningState(m_hero_, true);
}

HeroState* StandState::RightKeyDown() {
	return new RunningState(m_hero_, false);
}

HeroState* StandState::JumpKeyDown() {
	return new JumpState(m_hero_);
}

HeroState* StandState::Onland() {
	m_isOnland_ = true;
	return nullptr;
}

HeroState* StandState::Update() {
	if (!m_isOnland_) return new FallingState(m_hero_);
	m_isOnland_ = false;
	return nullptr;
}
