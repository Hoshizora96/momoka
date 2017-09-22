#pragma once
#include "objects/Entity.h"
#include "fsm/HeroState.h"

class Hero : public Entity {

public:
	explicit Hero();

	~Hero();
	void Update() override;
	void Render(float dt) override;


	void MoveLeft() override;
	void MoveRight() override;
	void MoveUp() override;
	void MoveDown() override;

	void Jump() override;

	void HandleInput(KEY_HERO keyHero);
	bool SwitchState(HeroState* state);
private:
	float m_movingVelocity_;
	HeroState* m_state_;
};
