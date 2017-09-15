#pragma once
#include "objects/Entity.h"

class Actor : public Entity {

public:
	~Actor() override;

	float GetVelocityX();
	float GetVelocityY();

	bool Update() override;
	bool Render(float dt) override;

	virtual bool MoveLeft();
	virtual bool MoveRight();
	virtual bool MoveUp();
	virtual bool MoveDown();

protected:
	float m_velocityX_;
	float m_velocityY_;
};
