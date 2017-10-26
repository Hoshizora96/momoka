#pragma once
#include "fsm/HeroState.h"

class JumpState : public HeroState {

public:
	explicit JumpState(Hero& hero);

	~JumpState() override;
	HeroState* JumpKeyState(INPUT_KEY_EVENT keyEvent) override;
	HeroState* Update() override;

private:
	float m_jumpingDate_;
};
