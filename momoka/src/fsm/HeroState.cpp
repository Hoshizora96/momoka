#include "stdafx.h"
#include "fsm/HeroState.h"

HeroState::HeroState(Hero& hero) : m_hero_(hero){
}

HeroState* HeroState::LeftKeyDown() {
	m_hero_.SetVelocityX(-m_hero_.GetDefaultHorizontalVelocity());
	return nullptr;
}

HeroState* HeroState::RightKeyDown() {
	m_hero_.SetVelocityX(m_hero_.GetDefaultHorizontalVelocity());
	return nullptr;
}

HeroState* HeroState::JumpKeyDown() {
	return nullptr;
}

HeroState* HeroState::Onland() {
	return nullptr;
}

HeroState* HeroState::Update() {
	return nullptr;
}
