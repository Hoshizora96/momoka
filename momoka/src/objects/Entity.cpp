#pragma once
#include "stdafx.h"
#include "objects/Entity.h"

Entity::~Entity() {
}

float Entity::GetX() {
	return m_posX_;
}

float Entity::GetY() {
	return m_posY_;
}

float Entity::GetCollisionWidth() {
	return m_collisionWidth_;
}

float Entity::GetCollisionHeight() {
	return m_collisionHeight_;
}

bool Entity::IsObstructive() {
	return m_isObstructive_;
}

bool Entity::HasGravity() {
	return m_hasGravity_;
}

void Entity::Update() {
}

void Entity::Render(float dt) {
}

void Entity::SetX(float x) {
	m_posX_ = x;
}

void Entity::SetY(float y) {
	m_posY_ = y;
}
