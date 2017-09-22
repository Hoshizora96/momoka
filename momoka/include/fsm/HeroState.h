#pragma once
#include "objects/Hero.h" 
#include "global.h"

class HeroState {
public:
	explicit HeroState(Hero& hero);
	virtual ~HeroState() = default;
	virtual HeroState* LeftKey(bool flag);
	virtual HeroState* RightKey(bool flag);
	virtual HeroState* JumpKey(bool flag);

	virtual HeroState* IsOnland(bool flag);

	Hero& m_hero_;
};