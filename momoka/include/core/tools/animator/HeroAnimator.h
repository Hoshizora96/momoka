#pragma once
#include "Animator.h"

class HeroAnimator : public Animator {

public:
	~HeroAnimator() override;
	inline bool Play(float& playingTime, AnimationType type, float x, float y) override;
};

inline HeroAnimator::~HeroAnimator() {
}

inline bool HeroAnimator::Play(float& playingTime, AnimationType type, float x, float y) {
	if(m_animations_==nullptr) {
		return false;
	}
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();

	switch (type) {
	case Stand:
		graphicService->DrawBitmap(m_animations_, x, y, 100, 100, 200, 0);
		break;
	default:
		return false;
	}
	return true;
}
