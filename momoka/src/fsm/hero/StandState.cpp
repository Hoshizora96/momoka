#include "stdafx.h"
#include "fsm/hero/StandState.h"
#include "fsm/hero/JumpState.h"

StandState::StandState(Hero& hero):HeroState(hero) {
}

HeroState* StandState::JumpKey(bool flag) {
	if(flag) {
		return new JumpState(m_hero_);
	}
	return nullptr;
}

HeroState* StandState::IsOnland(bool flag) {
	if(!flag) {
		
	}
	return nullptr;
}

