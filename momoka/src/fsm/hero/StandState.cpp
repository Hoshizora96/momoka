#include "stdafx.h"
//#include "fsm/hero/StandState.h"
//#include "fsm/hero/JumpState.h"
//#include "fsm/hero/RunningState.h"
//#include "fsm/hero/FallingState.h"
//#include "util/Log.h"
//
//StandState::StandState(Hero& hero)
//	: HeroState(hero) {
//	m_hero_.SetVelocityX(0);
//	m_hero_.SetVelocityY(0);
//	MOMOKA_LOG(momoka::debug) << "Switch to Stand State";
//}
//
//StandState::~StandState() {
//}
//
//HeroState* StandState::LeftKeyState(INPUT_KEY_EVENT keyEvent) {
//	if (keyEvent == Key_press || keyEvent == Key_down) {
//		return new RunningState(m_hero_, true);
//	}
//	return HeroState::LeftKeyState(keyEvent);
//}
//
//HeroState* StandState::RightKeyState(INPUT_KEY_EVENT keyEvent) {
//	if (keyEvent == Key_press || keyEvent == Key_down) {
//		return new RunningState(m_hero_, false);
//	}
//	return HeroState::RightKeyState(keyEvent);
//}
//
//HeroState* StandState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
//	if (keyEvent == Key_press) {
//		return new JumpState(m_hero_);
//	}
//	return HeroState::JumpKeyState(keyEvent);
//}
//
//HeroState* StandState::Onland() {
//	m_isOnland_ = true;
//	return nullptr;
//}
//
//HeroState* StandState::Update() {
//	if (!m_isOnland_) return new FallingState(m_hero_);
//	m_isOnland_ = false;
//	m_hero_.SetJumpNum(1);
//	return nullptr;
//}
