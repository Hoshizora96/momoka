#pragma once
#include "fsm/HeroState.h"

class StandState:public HeroState {
public:
	StandState(Hero& hero);
	HeroState* JumpKey(bool flag) override;
	HeroState* IsOnland(bool flag) override;
};