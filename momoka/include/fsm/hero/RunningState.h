#pragma once
#include "fsm/HeroState.h"

class RunningState : public HeroState {

public:
	explicit RunningState(Hero& hero, bool isMoveLeft);

	~RunningState() override;
	HeroState* LeftKeyDown() override;
	HeroState* RightKeyDown() override;
	HeroState* JumpKeyDown() override;
	HeroState* Onland() override;
	HeroState* Update() override;

private:
	bool m_isLeftKeyDown_;
	bool m_isRightKeyDown_;
	bool m_isJumpKeyDown_;
	bool m_isOnland_;
};
