#pragma once
#include "objects/Actor.h"

class Hero : public Actor {

public:
	explicit Hero();

	~Hero();
	void Update() override;
	void Render(float dt) override;


	void MoveLeft() override;
	void MoveRight() override;
	void MoveUp() override;
	void MoveDown() override;

private:
	float m_movingVelocity_;
};
