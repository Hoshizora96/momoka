#pragma once
#include "fsm/HeroState.h"

class FallingState : public HeroState {

public:
	explicit FallingState(Hero& hero);

	~FallingState() override;
	HeroState* Onland() override;
	HeroState* Update(float dt) override;
	HeroState* JumpKeyState(INPUT_KEY_EVENT keyEvent) override;
};
