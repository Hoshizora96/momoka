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

HeroState* FallingState::Update(float dt) {
	if (m_hero_.physicalBody.GetVelocity().GetY() < 1300.f) {
		auto velocity = m_hero_.physicalBody.GetVelocity();
		velocity.SetY(velocity.GetY() + 200);
		m_hero_.physicalBody.SetVelocity(velocity);
	}
	return HeroState::Update(dt);
}