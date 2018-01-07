#pragma once
#include "stdafx.h"
#include <set>
#include "Engine.h"
#include "services/GraphicService.h"

class Animator {
protected:
	ID2D1Bitmap* m_animations_ = nullptr;

public:
	enum AnimationType {
		Stand, Running, RunningShoot, Jump, JumpShoot, BeingAttacked
	};
	virtual ~Animator() = default;
	Animator();
	bool LoadAnimationSet(LPWSTR path);
	virtual bool Play(float& playingTime, AnimationType type, float x, float y);
};

inline Animator::Animator() {
}

inline bool Animator::LoadAnimationSet(LPWSTR path) {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	return graphicService->LoadBitMap(path, &m_animations_);
}

inline bool Animator::Play(float& playingTime, AnimationType type, float x, float y) {
	return false;
}
