#pragma once
#include "stdafx.h"
#include <set>
#include "Engine.h"
#include "services/GraphicService.h"

class Animator {
protected:
	ID2D1Bitmap* m_animations_ = nullptr;
	ID2D1Bitmap* m_animationsFlip_ = nullptr;

public:
	enum AnimationType {
		Shoot = 1,
		Stand = 1 << 1,
		Running = 1 << 2,
		Jump = 1 << 3,
		BeingAttacked = 1 << 4
	};

	virtual ~Animator() = default;
	Animator();
	bool LoadAnimationSet(LPWSTR path, LPWSTR pathFlip = nullptr);
	virtual bool Play(float& playingTime, AnimationType type, float x, float y, DIRECTION direction = Right);
	virtual bool SwitchAnimation(float& playingTime, AnimationType& current, AnimationType expected);
};

inline Animator::Animator() {
}

inline bool Animator::LoadAnimationSet(LPWSTR path, LPWSTR pathFlip) {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	auto res1 = graphicService->LoadBitMap(path, &m_animations_);
	if(pathFlip) {
		auto res2 = graphicService->LoadBitMap(pathFlip, &m_animationsFlip_);
		return res1 && res2;
	}
	return res1;
}

inline bool Animator::Play(float& playingTime, AnimationType type, float x, float y, DIRECTION direction) {
	return false;
}

inline bool Animator::SwitchAnimation(float& playingTime, AnimationType& current, AnimationType expected) {
	if (int(current & expected) != 0) return false;
	switch(expected) {
	case Shoot:
		if (current == BeingAttacked)
			return false;
		current = AnimationType(current | Shoot);
		playingTime = 0;
		return true;
	default:
		current = expected;
		playingTime = 0;
		return true;
	}
	return false;
}
