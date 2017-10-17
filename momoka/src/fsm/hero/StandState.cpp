#include "stdafx.h"
#include "fsm/hero/StandState.h"
#include "fsm/hero/JumpState.h"

StandState::StandState(Hero& hero)
	: HeroState(hero) {
	m_hero_.SetVelocityX(0);
	m_hero_.SetVelocityY(0);
}

StandState::~StandState() {
}

HeroState* StandState::LeftKeyDown() {
	return nullptr;
}

HeroState* StandState::RightKeyDown() {
	return nullptr;
}

HeroState* StandState::JumpKeyDown() {
	return new JumpState(m_hero_);
}
