#include "stdafx.h"
#include "fsm/hero/FallingState.h"
#include "fsm/hero/StandState.h"
#include "util/Log.h"

FallingState::FallingState(Hero& hero)
	: HeroState(hero) {
	MOMOKA_LOG(momoka::debug) << "Switch to Falling State";
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
	return HeroState::Update();
}
