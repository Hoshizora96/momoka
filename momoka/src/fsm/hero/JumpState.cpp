#include "stdafx.h"
#include "fsm/hero/JumpState.h"
#include "fsm/hero/FallingState.h"
#include "util/Log.h"

JumpState::JumpState(Hero& hero)
	: HeroState(hero), m_isJumpKeyDown_(true), m_jumpingDate_(0) {
	m_hero_.SetVelocityY(-1200);
	MOMOKA_LOG(momoka::debug) << "Switch to Jump State";
}

JumpState::~JumpState() {
}

HeroState* JumpState::JumpKeyDown() {
	m_isJumpKeyDown_ = true;
	return nullptr;
}

HeroState* JumpState::Update() {
	if(m_isJumpKeyDown_) {
		m_jumpingDate_ += 1 / momoka_global::REFRESH_RATE;
		if(m_jumpingDate_ > 0.15) {
			return new FallingState(m_hero_);
		}
		m_isJumpKeyDown_ = false;
		return nullptr;
	}
	else {
		return new FallingState(m_hero_);
	}
}
