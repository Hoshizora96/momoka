#include "stdafx.h"
#include "fsm/hero/FallingState.h"
#include "fsm/hero/StandState.h"

FallingState::FallingState(Hero& hero)
	: HeroState(hero) {
}

FallingState::~FallingState() {
}

HeroState* FallingState::Onland() {
	return new StandState(m_hero_);
}

HeroState* FallingState::Update() {
	if (m_hero_.GetVelocityY() < 1300.f) {
		m_hero_.SetVelocityY(m_hero_.GetVelocityY() + 200);
	}
	return nullptr;
}
