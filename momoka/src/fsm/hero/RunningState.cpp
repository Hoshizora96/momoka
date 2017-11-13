#include "stdafx.h"
//#include "fsm/hero/RunningState.h"
//#include "fsm/hero/FallingState.h"
//#include "fsm/hero/JumpState.h"
//#include "fsm/hero/StandState.h"
//#include "util/Log.h"
//
//RunningState::RunningState(Hero& hero, bool isMoveLeft)
//	: HeroState(hero) {
//	if(isMoveLeft) {
//		m_hero_.SetVelocityX(-m_hero_.GetDefaultHorizontalVelocity());
//	}
//	else {
//		m_hero_.SetVelocityX(m_hero_.GetDefaultHorizontalVelocity());
//	}
//
//	MOMOKA_LOG(momoka::debug) << "Switch to Running State";
//}
//
//RunningState::~RunningState() {
//}
//
//HeroState* RunningState::LeftKeyState(INPUT_KEY_EVENT keyEvent) {
//	if(keyEvent == Key_release) {
//		return new StandState(m_hero_);
//	}
//	return HeroState::LeftKeyState(keyEvent);
//}
//
//HeroState* RunningState::RightKeyState(INPUT_KEY_EVENT keyEvent) {
//	if (keyEvent == Key_release) {
//		return new StandState(m_hero_);
//	}
//	return HeroState::RightKeyState(keyEvent);
//}
//
//HeroState* RunningState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
//	if(keyEvent == Key_press) {
//		return new JumpState(m_hero_);
//	}
//	return HeroState::JumpKeyState(keyEvent);
//}
//
//HeroState* RunningState::Onland() {
//	m_isOnland_ = true;
//	return nullptr;
//}
//
//HeroState* RunningState::Update() {
//	if (!m_isOnland_) 
//		return new FallingState(m_hero_);
//	return HeroState::Update();
//}
