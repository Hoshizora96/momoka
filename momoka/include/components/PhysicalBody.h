#pragma once
#include "util/Vector2.h"

class PhysicalBody {
private:
	Vector2<float> m_position_;
	Vector2<float> m_velocity_;
	Vector2<float> m_bodySize_;

	bool m_isOnGround_;

public:
	Vector2<float> GetPosition();
	Vector2<float> GetVelocity();
	Vector2<float> GetBodySize();

	Vector2<float> SetPosition(Vector2<float>& position);
	Vector2<float> SetVelocity(Vector2<float>& position);
	Vector2<float> SetBodySize(Vector2<float>& position);
};
