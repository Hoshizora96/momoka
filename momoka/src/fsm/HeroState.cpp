#include "stdafx.h"
//#include "fsm/HeroState.h"
//
//HeroState::HeroState(Hero& hero) : m_hero_(hero),
//                                   m_isOnland_(true) {
//}
//
//void HeroState::ClearFlag() {
//	m_isOnland_ = false;
//}
//
//HeroState* HeroState::LeftKeyState(INPUT_KEY_EVENT keyEvent) {
//	if(keyEvent == Key_press || keyEvent == Key_down) {
//		m_hero_.SetVelocityX(-m_hero_.GetDefaultHorizontalVelocity());
//	}
//	else if(keyEvent == Key_release) {
//		m_hero_.SetVelocityX(0);
//	}
//	return nullptr;
//}
//
//HeroState* HeroState::RightKeyState(INPUT_KEY_EVENT keyEvent) {
//	if (keyEvent == Key_press || keyEvent == Key_down) {
//		m_hero_.SetVelocityX(m_hero_.GetDefaultHorizontalVelocity());
//	}
//	else if (keyEvent == Key_release) {
//		m_hero_.SetVelocityX(0);
//	}
//	return nullptr;
//}
//
//HeroState* HeroState::JumpKeyState(INPUT_KEY_EVENT keyEvent) {
//	return nullptr;
//}
//
//HeroState* HeroState::Onland() {
//	return nullptr;
//}
//
//HeroState* HeroState::Update() {
//	ClearFlag();
//	return nullptr;
//}
