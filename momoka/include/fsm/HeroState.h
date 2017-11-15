#pragma once
#include "objects/Hero.h" 
#include "services/InputService.h"

class Hero;
class HeroState {
public:
	explicit HeroState(Hero& hero);
	virtual ~HeroState() = default;

	void ClearFlag();

	virtual HeroState* LeftKeyState(INPUT_KEY_EVENT keyEvent);
	virtual HeroState* RightKeyState(INPUT_KEY_EVENT keyEvent);
	virtual HeroState* JumpKeyState(INPUT_KEY_EVENT keyEvent);

	virtual HeroState* Onland();
	virtual HeroState* Update(float dt);
protected:
	Hero& m_hero_;

	bool m_isOnland_;
};
