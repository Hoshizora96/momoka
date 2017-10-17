#pragma once
#include "fsm/HeroState.h"

class FallingState : public HeroState {

public:
	explicit FallingState(Hero& hero)
		: HeroState(hero) {
	}

	~FallingState() override;
	HeroState* Onland() override;
	HeroState* Update() override;
};
