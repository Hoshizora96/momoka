#pragma once
#include "fsm/HeroState.h"

class FallingState: public HeroState {

public:
	HeroState* IsOnland(bool flag) override;
};
