#pragma once
#include "util/Vector2.h"

class PhysicalBody {
private:
	Vector2<float> m_position_;
	Vector2<float> m_velocity_;
	Vector2<float> m_bodySize_;

	bool m_isOnGround_;
	float m_movingVelocity_;

public:
	PhysicalBody();

	Vector2<float> GetPosition() const;
	Vector2<float> GetVelocity() const;
	Vector2<float> GetBodySize() const;

	float GetMovingVelocity() const;
	void SetMovingVelocity(float velocity);

	void SetPosition(Vector2<float>& position);
	void SetPosition(float x, float y);
	void SetVelocity(Vector2<float>& velocity);
	void SetVelocity(float velocityX, float velocityY);
	void SetBodySize(Vector2<float>& size);
	void SetBodySize(float width, float height);
};
