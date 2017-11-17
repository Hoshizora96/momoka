#pragma once
#include "util/Vector2.h"
#include "components/HitBox.h"
class Camera {
public:
	Camera();

	float Scale(const float &val) const;

	Vector2<float> TransformedCoordinate(const float& x, const float& y) const;
	float TransformedLength(const float& length) const;

	// 只要把游戏实际的坐标传入就好了，里面会负责自动转换绘制
	void DrawRect(const float& x, const float& y, const float& width, const float& height) const;
private:
	HitBox m_hitBox_;

	float m_centerX_;
	float m_centerY_;
	float m_viewWidth_;
	float m_viewHeight_;

	float m_scaleRatio_;

	bool m_xLock_;
	bool m_yLock_;
};