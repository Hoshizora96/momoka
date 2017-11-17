#include "stdafx.h"
#include "components/Camera.h"
#include "services/GraphicService.h"
#include "Engine.h"

Camera::Camera(): m_centerX_(1280/2), m_centerY_(960/2), m_viewWidth_(1280), m_viewHeight_(960), m_scaleRatio_(1), m_xLock_(false),
                  m_yLock_(false) {
	// TODO: ���ĳ�ʼ�����������ﴰ�ڴ�С��д����
}

float Camera::Scale(const float& val) const {
	return val * m_scaleRatio_;
}

Vector2<float> Camera::TransformedCoordinate(const float& x, const float& y) const {
	float cameraX = x - (m_centerX_ - m_viewWidth_/2);
	float cameraY = y - (m_centerY_ - m_viewHeight_/2);

	float scaledX = m_centerX_ - Scale(m_centerX_ - cameraX);
	float scaledY = m_centerY_ - Scale(m_centerY_ - cameraY);

	return Vector2<float>(scaledX, scaledY);
}

float Camera::TransformedLength(const float& length) const {
	return Scale(length);
}

void Camera::DrawRect(const float& x, const float& y, const float& width, const float& height) const {
	// TODO: ����жϣ�����Ƿ��������ڣ����������ھͲ�����
	const auto pGraphicService = Engine::serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();

	auto coordinate = TransformedCoordinate(x, y);

	pGraphicService->DrawRect(coordinate.GetX(), coordinate.GetY(), TransformedLength(width), TransformedLength(height));
}

void Camera::LookAt(float x, float y) {
	m_centerX_ = x;
	m_centerY_ = y;
}
