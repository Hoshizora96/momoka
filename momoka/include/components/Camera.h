#pragma once
#include "util/Vector2.h"
#include "components/HitBox.h"
class Camera {
public:
	Vector2<float> ViewTransform(Vector2<float>& position) const;
private:
	HitBox m_hitBox_;

	float m_posX_;
	float m_posY_;
	float m_screenWidth_;
	float m_screenHeight_;

	float m_activeWidth_;
	float m_activeHeight_;

	float m_scaleRatio_;

	bool m_xLock_;
	bool m_yLock_;
};