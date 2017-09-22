#pragma once
#include "fsm/HeroState.h"

class JumpState: public HeroState {
public:
	explicit JumpState(Hero& hero);

	~JumpState() override;
	HeroState* JumpKey(bool flag) override;
private:
	float m_floatTime_;
};
