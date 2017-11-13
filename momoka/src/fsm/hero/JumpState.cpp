#include "stdafx.h"
//#include "fsm/hero/JumpState.h"
//#include "fsm/hero/FallingState.h"
//#include "util/Log.h"
//
//JumpState::JumpState(Hero& hero)
//	: HeroState(hero), m_jumpingDate_(0) {
//	m_hero_.SetVelocityY(-1200);
//	MOMOKA_LOG(momoka::debug) << "Switch to Jump State";
//}
//
//JumpState::~JumpState() {
//}
//
//HeroState* JumpState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
//	if(keyEvent == Key_release) {
//		return new FallingState(m_hero_);
//	}
//	return HeroState::JumpKeyState(keyEvent);
//}
//
//HeroState* JumpState::Update() {
//	if (m_hero_.GetVelocityY() != 0) {  // 判断有没有碰到顶
//		m_jumpingDate_ += 1 / momoka_global::REFRESH_RATE;
//		if (m_jumpingDate_ > 0.15) {
//			return new FallingState(m_hero_);
//		}
//		return HeroState::Update();
//	}
//	else {
//		return new FallingState(m_hero_);
//	}
//}
