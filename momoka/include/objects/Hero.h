#pragma once
#include "objects/Entity.h"
#include "fsm/HeroState.h"
class HeroState;
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

	bool SwitchState(HeroState* state);
	void Onland() override;
private:
	float m_movingVelocity_;
	HeroState* m_state_;
};
