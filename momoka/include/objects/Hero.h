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

	void Onland() override;

	int GetJumpNum() const;
	void SetJumpNum(int);

	float GetDefaultHorizontalVelocity() const;

private:
	void HandleInput() override;
	bool SwitchState(HeroState* state);

	float m_defaultHorizontalVelocity_;
	HeroState* m_state_;
	int m_jumpnumber_;
};
