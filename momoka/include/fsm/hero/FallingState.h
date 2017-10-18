#pragma once
#include "fsm/HeroState.h"

class FallingState : public HeroState {

public:
	explicit FallingState(Hero& hero);

	~FallingState() override;
	HeroState* Onland() override;
	HeroState* Update() override;
};
