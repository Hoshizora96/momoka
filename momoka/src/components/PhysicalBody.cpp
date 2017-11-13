#include "stdafx.h"
#include "components/PhysicalBody.h"

Vector2<float> PhysicalBody::GetPosition() {
	return m_position_;
}

Vector2<float> PhysicalBody::GetVelocity() {
	return m_velocity_;
}

Vector2<float> PhysicalBody::GetBodySize() {
	return m_bodySize_;
}

Vector2<float> PhysicalBody::SetPosition(Vector2<float>& position) {
}

Vector2<float> PhysicalBody::SetVelocity(Vector2<float>& position) {
}

Vector2<float> PhysicalBody::SetBodySize(Vector2<float>& position) {
}

