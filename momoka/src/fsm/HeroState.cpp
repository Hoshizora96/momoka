#include "stdafx.h"
#include "fsm/HeroState.h"

HeroState::HeroState(Hero& hero) : m_hero_(hero){
}

HeroState* HeroState::LeftKeyDown() {

	return nullptr;
}

HeroState* HeroState::RightKeyDown() {
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
