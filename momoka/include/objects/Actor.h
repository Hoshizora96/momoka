#pragma once
#include "objects/Entity.h"

class Actor : public Entity {

public:
	~Actor() override;

	float GetVelocityX();
	float GetVelocityY();

	void Update() override;
	void Render(float dt) override;

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveUp();
	virtual void MoveDown();

protected:
	float m_velocityX_;
	float m_velocityY_;
};

inline Actor::~Actor() {
}

inline float Actor::GetVelocityX() {
}

inline float Actor::GetVelocityY() {
}

inline void Actor::Update() {
}

inline void Actor::Render(float dt) {
}

inline void Actor::MoveLeft() {
}

inline void Actor::MoveRight() {
}

inline void Actor::MoveUp() {
}

inline void Actor::MoveDown() {
}

