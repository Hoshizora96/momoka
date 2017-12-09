#pragma once
#include "util/Vector2.h"
namespace utility {
	inline bool CollisionDetector(Vector2F pos1, Vector2F size1, Vector2F pos2, Vector2F size2) {
		bool xCross = pos1.GetX() >= pos2.GetX() + size2.GetX()
			^ pos1.GetX() + size1.GetX() >= pos2.GetX();
		bool yCross = pos1.GetY() >= pos2.GetY() + size2.GetY()
			^ pos1.GetY() + size1.GetY() >= pos2.GetY();
		return xCross && yCross;
	}
}