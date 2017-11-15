#pragma once
#include "fsm/HeroState.h"

class StandState : public HeroState {

public:
	explicit StandState(Hero& hero);

	~StandState() override;
	HeroState* LeftKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* RightKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* JumpKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* Onland() override;
	HeroState* Update(float dt) override;
};
