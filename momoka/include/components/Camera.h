#pragma once
class Camera {
private:
	float m_posX_;
	float m_posY_;
	float m_screenWidth_;
	float m_screenHeight_;

	float m_scaleRatio_;

	bool m_xLock_;
	bool m_yLock_;
};