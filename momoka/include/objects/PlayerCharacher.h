#pragma once
#include "objects/Entity.h"

class PlayerCharacter : public Entity {

public:
	~PlayerCharacter() override;
	float GetX() override;
	float GetY() override;
	bool OnEvent() override;
	float GetVelocityX() override;
	float GetVelocityY() override;
	float GetCollisionWidth() override;
	float GetCollisionHeight() override;
	bool IsObstructive() override;
	bool PlayerControlHandle() override;
	bool Update(float dt) override;
	bool Render() override;
};


