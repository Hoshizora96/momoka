#pragma once
#include "Animator.h"

class HeroAnimator : public Animator {

public:
	~HeroAnimator() override;
	inline bool Play(float& playingTime, AnimationType type, float x, float y, DIRECTION direction = Right) override;
};

inline HeroAnimator::~HeroAnimator() {
}

inline bool HeroAnimator::Play(float& playingTime, AnimationType type, float x, float y, DIRECTION direction) {
	if (m_animations_ == nullptr) {
		return false;
	}
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();

	if (direction == Right) {
		if (type == BeingAttacked) {
			auto i = int(playingTime / 0.05) % 2;
			switch (i) {
			case 0:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 400, 0);
				return true;
			case 1:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 500, 0);
				return true;
			default:
				return false;
			}
		}

		if (type == (Stand | Shoot)) {
			graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 500, 100);
			return true;
		}

		if (type == Stand) {
			graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 0, 0);
			return true;
		}

		if (type == (Running | Shoot)) {
			auto i = int(playingTime / 0.1) % 4;
			switch (i) {
			case 0:
			case 2:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 100, 100);
				return true;
			case 1:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 200, 100);
				return true;
			case 3:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 300, 100);
				return true;
			default:
				return false;
			}
		}

		if (type == Running) {
			auto i = int(playingTime / 0.1) % 4;
			switch (i) {
			case 0:
			case 2:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 100, 0);
				return true;
			case 1:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 200, 0);
				return true;
			case 3:
				graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 300, 0);
				return true;
			default:
				return false;
			}
		}

		if (type == Jump | Shoot) {
			graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 400, 100);
			return true;
		}

		if (type == Jump) {
			graphicService->DrawBitmap(m_animations_, x - 20, y + 20, 100, 100, 0, 100);
			return true;
		}
	}
	else {
		if (type == BeingAttacked) {
			auto i = int(playingTime / 0.05) % 2;
			switch (i) {
			case 0:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 100, 0);
				return true;
			case 1:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 0, 0);
				return true;
			default:
				return false;
			}
		}

		if (type == (Stand | Shoot)) {
			graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 0, 100);
			return true;
		}

		if (type == Stand) {
			graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 500, 0);
			return true;
		}

		if (type == (Running | Shoot)) {
			auto i = int(playingTime / 0.1) % 4;
			switch (i) {
			case 0:
			case 2:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 400, 100);
				return true;
			case 1:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 300, 100);
				return true;
			case 3:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 200, 100);
				return true;
			default:
				return false;
			}
		}

		if (type == Running) {
			auto i = int(playingTime / 0.1) % 4;
			switch (i) {
			case 0:
			case 2:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 400, 0);
				return true;
			case 1:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 300, 0);
				return true;
			case 3:
				graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 200, 0);
				return true;
			default:
				return false;
			}
		}

		if (type == Jump | Shoot) {
			graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 100, 100);
			return true;
		}

		if (type == Jump) {
			graphicService->DrawBitmap(m_animationsFlip_, x - 20, y + 20, 100, 100, 500, 100);
			return true;
		}
	}
	return false;
}
