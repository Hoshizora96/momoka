#pragma once
#include "util/Vector2.h"

class PhysicalBody {
private:
	Vector2<float> m_position;
	Vector2<float> m_velocity;
	Vector2<float> m_bodySize;

	bool m_isOnGround;
	float m_defaultMovingVelocity;

public:
	PhysicalBody();

	Vector2<float> GetPosition() const;
	Vector2<float> GetVelocity() const;
	Vector2<float> GetBodySize() const;

	float GetDefaultHorizonalVelocity() const;
	void SetDefaultHorizonalVelocity(float velocity);

	void SetPosition(Vector2<float>& position);
	void SetPosition(float x, float y);
	void SetVelocity(Vector2<float>& velocity);
	void SetVelocity(float velocityX, float velocityY);
	void SetBodySize(Vector2<float>& size);
	void SetBodySize(float width, float height);
};
