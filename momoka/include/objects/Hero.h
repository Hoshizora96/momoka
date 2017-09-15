#pragma once
#include "objects/Actor.h"

class Hero : public Actor {

public:
	explicit Hero();

	~Hero();
	bool Update() override;
	bool Render(float dt) override;


	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveUp() override;
	bool MoveDown() override;

private:
	float m_movingVelocity_;
};
