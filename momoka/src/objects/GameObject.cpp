#include "stdafx.h"
#include "objects/GameObject.h"

unsigned int GameObject::m_nextId_ = 0;
int GameObject::GenerateObjectId() {
	return m_nextId_++;
}

GameObject::GameObject(int id): m_id_(id), m_isActive_(true) {

}

int GameObject::GetId() const {
	return m_id_;
}

bool GameObject::IsActive() const {
	return m_isActive_;
}

void GameObject::SetActive(bool active) {
	m_isActive_ = active;
}

void GameObject::Update(float dt) {
}

