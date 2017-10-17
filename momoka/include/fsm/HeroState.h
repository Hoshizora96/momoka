#pragma once
#include "objects/Hero.h" 
class Hero;
class HeroState {
public:
	explicit HeroState(Hero& hero);
	virtual ~HeroState() = default;
	virtual HeroState* LeftKeyDown();
	virtual HeroState* RightKeyDown();
	virtual HeroState* JumpKeyDown();

	virtual HeroState* Onland();
	virtual HeroState* Update();
protected:
	Hero& m_hero_;
};



