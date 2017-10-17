#pragma once
#include "fsm/HeroState.h"

class JumpState : public HeroState {

public:
	explicit JumpState(Hero& hero);

	~JumpState() override;
	HeroState* JumpKeyDown() override;
	HeroState* Update() override;

private:
	float m_jumpingDate_;
	bool m_isJumpKeyDown_;
};
