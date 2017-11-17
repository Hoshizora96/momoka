#include "stdafx.h"
#include "Engine.h"
#include "objects/Hero.h"
#include "services/GraphicService.h"
#include "fsm/HeroState.h"
#include "fsm/hero/StandState.h"
#include "services/InputService.h"
#include "util/JsonTools.h"
#include "util/Log.h"

void Hero::Render(Camera* camera) {
	camera->LookAt(GetX(), GetY());
	if(camera != nullptr) {
		m_world_.GetCamera()->DrawRect(GetX(), GetY(), momoka_global::TILE_SIZE, momoka_global::TILE_SIZE * 2);
	}
	else {
		MOMOKA_LOG(momoka::warning) << "No camera provided, it will do nothing.";
	}
	
}

bool Hero::SwitchState(HeroState* state) {
	if (state != nullptr) {
		SafeDelete(&m_state_);
		m_state_ = state;
		return true;
	}
	return false;
}

void Hero::HandleCollisionInfo(CollisionInfo info) {
	// 这里是默认情况，要想定制新的情况就修改这里的函数
	if (info.isOnGround) {
		SwitchState(m_state_->Onland());
	}
	m_physicalBody_.SetPosition(info.correctedX, info.correctedY);
	m_physicalBody_.SetVelocity(info.correctedVelocityX, info.correctedVelocityY);
}

bool Hero::LoadConfig(char* path) {
	rapidjson::Document d;
	// "content/tiles/tile-type-test.json"
	if (LoadJsonFile(d, path)) {
		m_physicalBody_.SetMovingVelocity(d["defaultHorizonalVelocity"].GetFloat());
		return true;
	}
	return false;
}

void Hero::HandleInput() {
	const auto pInputService = Engine::serviceLoader.LocateService<InputService>(SERVICE_TYPE::Service_input).
	                                                   lock();

	if (pInputService->IsKeyEventHappened(DIK_A, Key_down)) {
		SwitchState(m_state_->LeftKeyState(Key_down));
	}
	if (pInputService->IsKeyEventHappened(DIK_A, Key_release)) {
		SwitchState(m_state_->LeftKeyState(Key_release));
	}

	if (pInputService->IsKeyEventHappened(DIK_D, Key_down)) {
		SwitchState(m_state_->RightKeyState(Key_down));
	}
	if (pInputService->IsKeyEventHappened(DIK_D, Key_release)) {
		SwitchState(m_state_->RightKeyState(Key_release));
	}

	if (pInputService->IsKeyEventHappened(DIK_K, Key_press)) {
		SwitchState(m_state_->JumpKeyState(Key_press));
	}
	if (pInputService->IsKeyEventHappened(DIK_K, Key_release)) {
		SwitchState(m_state_->JumpKeyState(Key_release));
	}
}


Hero::~Hero() {
}

Hero::Hero(World& world): Entity(), m_state_(nullptr), m_jumpnumber_(0), m_world_(world) {
	m_state_ = new StandState(*this);
	m_physicalBody_.SetVelocity(0, 0);
	m_physicalBody_.SetBodySize(momoka_global::TILE_SIZE, momoka_global::TILE_SIZE * 2);
	m_physicalBody_.SetPosition(0, 0);
}

int Hero::GetJumpNum() const {
	return this->m_jumpnumber_;
}

void Hero::SetJumpNum(int num) {
	m_jumpnumber_ = num;
}

void Hero::Update(float dt) {
	HandleInput();

	auto velocity = m_physicalBody_.GetVelocity();
	auto position = m_physicalBody_.GetPosition();
	m_physicalBody_.SetPosition(position.GetX() + velocity.GetX() * dt, position.GetY() + velocity.GetY() * dt);

	//	m_physicalBody_=m_nextFramePhysicalBody_;

	SwitchState(m_state_->Update(dt));

	auto info = m_world_.GetCollisionDetector().CheckTileCollision(m_physicalBody_);
	HandleCollisionInfo(info);
}
