#include "stdafx.h"
#include "fsm/hero/JumpState.h"
#include "fsm/hero/FallingState.h"
#include "util/Log.h"

JumpState::JumpState(Hero& hero)
	: HeroState(hero), m_jumpingDate(0) {
	m_hero_.physicalBody.SetVelocity(
		m_hero_.physicalBody.GetVelocity().GetX(),
		-1200);
	MOMOKA_LOG(momoka::debug) << "Switch to Jump State";
}

JumpState::~JumpState() {
}

HeroState* JumpState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
	if (keyEvent == Key_release) {
		return new FallingState(m_hero_);
	}
	return HeroState::JumpKeyState(keyEvent);
}

HeroState* JumpState::Update(float dt) {
	if (m_hero_.physicalBody.GetVelocity().GetY() != 0) {
		// 判断有没有碰到顶
		m_jumpingDate += 1 / momoka_global::REFRESH_RATE;
		if (m_jumpingDate > 0.15) {
			return new FallingState(m_hero_);
		}
		return HeroState::Update(dt);
	}
	else {
		return new FallingState(m_hero_);
	}
}
