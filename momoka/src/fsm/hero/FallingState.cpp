#include "stdafx.h"
#include "fsm/hero/FallingState.h"
#include "fsm/hero/StandState.h"
#include "util/Log.h"
#include "fsm/hero/JumpState.h"

FallingState::FallingState(Hero& hero)
	: HeroState(hero) {
	MOMOKA_LOG(momoka::debug) << "Switch to Falling State";
}

FallingState::~FallingState() {
}

HeroState* FallingState::Onland() {
	return new StandState(m_hero_);
}


HeroState* FallingState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
	if (keyEvent == Key_press) {
		int jumpnum = m_hero_.GetJumpNum();
		if (jumpnum > 0) {
			m_hero_.SetJumpNum(jumpnum - 1);
			return new JumpState(m_hero_);
		}
		return new FallingState(m_hero_);
	}
	return HeroState::JumpKeyState(keyEvent);
}

HeroState* FallingState::Update() {
	if (m_hero_.GetVelocityY() < 1300.f) {
		m_hero_.SetVelocityY(m_hero_.GetVelocityY() + 200);
	}
	if (m_hero_.GetY() > 800) {
		return nullptr;
	}
	return HeroState::Update();
}