#include "stdafx.h"
#include "objects/Entity.h"

Entity::~Entity() {
}

float Entity::GetX() const {
	return m_physicalBody_.posX;
}

float Entity::GetY() const {
	return m_physicalBody_.posY;
}

void Entity::SetCollisionDetector(CollisionDetector* pCollisionDetector) {
	m_pCollisionDetector_ = pCollisionDetector;
}

void Entity::Update() {
}

void Entity::Render(float dt) {
}

void Entity::MoveLeft() {
}

void Entity::MoveRight() {
}

void Entity::MoveUp() {
}

void Entity::MoveDown() {
}

void Entity::Jump() {
}

void Entity::Onland() {
}

void Entity::SetX(float velocityX) {
	m_physicalBody_.velocityX = velocityX;
}

void Entity::SetY(float velocityY) {
	m_physicalBody_.velocityX = velocityY;
}

float Entity::GetVelocityX() const {
	return m_physicalBody_.velocityX;
}

float Entity::GetVelocityY() const {
	return m_physicalBody_.velocityY;
}

void Entity::SetVelocityX(float velocityX) {
	m_physicalBody_.velocityX = velocityX;
}

void Entity::SetVelocityY(float velocityY) {
	m_physicalBody_.velocityY = velocityY;
}

void Entity::SetOnLandFlag(bool flag) {
	m_isOnLand_ = flag;
}
