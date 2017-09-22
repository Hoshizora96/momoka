#include "stdafx.h"
#include "fsm/hero/JumpState.h"

JumpState::JumpState(Hero& hero): HeroState(hero),
                                  m_floatTime_(0) {
}

HeroState* JumpState::JumpKey(bool flag) {
	if (flag) {
		m_floatTime_ += 1.0f / REFRESH_RATE;
		if(m_floatTime_ > 0.8) {
			
		}
	}
	else {
		
	}
	return nullptr;
}
