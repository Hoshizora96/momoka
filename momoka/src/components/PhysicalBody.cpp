#include "stdafx.h"
#include "components/PhysicalBody.h"
#include "util/Log.h"

PhysicalBody::PhysicalBody(): m_isOnGround(false), m_defaultMovingVelocity(100) {

}

Vector2<float> PhysicalBody::GetPosition() const {
	return m_position;
}

Vector2<float> PhysicalBody::GetVelocity() const {
	return m_velocity;
}

Vector2<float> PhysicalBody::GetBodySize() const {
	return m_bodySize;
}

float PhysicalBody::GetDefaultHorizonalVelocity() const {
	return m_defaultMovingVelocity;
}

void PhysicalBody::SetDefaultHorizonalVelocity(float velocity) {
	if (velocity < 0) {
		MOMOKA_LOG(momoka::error) <<
			"Try to set default horizonal velocity with negative value: " << velocity <<
			", it will do nothing.";
		return;
	}
	m_defaultMovingVelocity = velocity;
}

void PhysicalBody::SetPosition(Vector2<float>& position) {
	if (position.GetX() < 0 || position.GetY() < 0) {
		MOMOKA_LOG(momoka::error) <<
			"Try to set position with negative value:" << position <<
			", it will turn to 0.";
		if (position.GetX() < 0) position.SetX(0);
		if (position.GetY() < 0) position.SetY(0);
	}
	m_position = position;
}

void PhysicalBody::SetPosition(float x, float y) {
	if (x < 0 || y < 0) {
		MOMOKA_LOG(momoka::error) <<
			"Try to set position with negative value:" << Vector2<float>(x, y) <<
			", it will turn to 0.";
		if (x < 0) x = 0;
		if (y < 0) y = 0;
	}
	m_position = Vector2<float>(x, y);
}

void PhysicalBody::SetVelocity(Vector2<float>& velocity) {
	m_velocity = velocity;
}

void PhysicalBody::SetVelocity(float velocityX, float velocityY) {
	m_velocity = Vector2<float>(velocityX, velocityY);
}

void PhysicalBody::SetBodySize(Vector2<float>& size) {
	if (size.GetX() < 0 || size.GetY() < 0) {
		MOMOKA_LOG(momoka::error) << "Try to set an negative size: " << size <<
			", it will do nothing.";
		return;
	}
	m_bodySize = size;
}

void PhysicalBody::SetBodySize(float width, float height) {
	if (width < 0 || height < 0) {
		MOMOKA_LOG(momoka::error) << "Try to set an negative size: " << Vector2<float>(width, height) <<
			", it will do nothing.";
		return;
	}
	m_bodySize = Vector2<float>(width, height);
}
