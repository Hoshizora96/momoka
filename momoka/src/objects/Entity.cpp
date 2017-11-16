#include "stdafx.h"
#include "objects/Entity.h"

Entity::~Entity() {
}

Entity::Entity(): GameObject(GameObject::GenerateObjectId()) {
}

void Entity::Update(float dt) {
}

void Entity::Render(float dt) {
}

bool Entity::LoadConfig(char* path) {
	return false;
}

Vector2<float> Entity::GetVelocity() {
	return m_physicalBody_.GetVelocity();
}

void Entity::SetVelocity(float vx, float vy) {
	m_physicalBody_.SetVelocity(vx, vy);
}

Vector2<float> Entity::GetPosition() {
	return m_physicalBody_.GetPosition();
}

float Entity::GetMovingVelocity() {
	return m_physicalBody_.GetMovingVelocity();
}

void Entity::SetPosition(float x, float y) {
	m_physicalBody_.SetVelocity(x, y);
}

void Entity::SetMovingVelocity(float velocity) {
	m_physicalBody_.SetMovingVelocity(velocity);
}

float Entity::GetVelocityX() {
	return m_physicalBody_.GetVelocity().GetX();
}

float Entity::GetVelocityY() {
	return m_physicalBody_.GetVelocity().GetY();
}

void Entity::SetVelocityX(float vx) {
	SetVelocity(vx, GetVelocityY());
}

void Entity::SetVelocityY(float vy) {
	SetVelocity(GetVelocityX(), vy);
}

float Entity::GetX() {
	return m_physicalBody_.GetPosition().GetX();
}

float Entity::GetY() {
	return m_physicalBody_.GetPosition().GetY();
}

void Entity::SetX(float x) {
	SetPosition(x, GetY());
}

void Entity::SetY(float y) {
	SetPosition(GetX(), y);
}

void Entity::HandleCollisionInfo(CollisionInfo info) {
}
