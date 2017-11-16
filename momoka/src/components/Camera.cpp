#include "stdafx.h"
#include "components/Camera.h"

Vector2<float> Camera::ViewTransform(Vector2<float>& position) const {
	Vector2<float> correctedPos;
	correctedPos.SetX(position.GetX() - m_posX_);
	correctedPos.SetY(position.GetY() - m_posY_);
	return correctedPos;
}
