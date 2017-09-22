#include "stdafx.h"
#include "fsm/HeroState.h"

HeroState::HeroState(Hero& hero) :m_hero_(hero){
}

HeroState* HeroState::LeftKey(bool flag) {
	if(flag) {
		m_hero_.MoveLeft();
	}
	else {
		if(m_hero_.GetVelocityX()<0) {
			m_hero_.SetVelocityX(0);
		}
	}
}

HeroState* HeroState::RightKey(bool flag) {
	if (flag) {
		m_hero_.MoveRight();
	}
	else {
		if (m_hero_.GetVelocityX()>0) {
			m_hero_.SetVelocityX(0);
		}
	}
}

HeroState* HeroState::JumpKey(bool flag) {
}

HeroState* HeroState::IsOnland(bool flag) {
}
