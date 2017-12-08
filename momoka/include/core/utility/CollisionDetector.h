#pragma once

inline bool CollisionDetector(float x1, float y1, float width1, float height1, float x2, float y2, float width2,
                       float height2) {
	if (x2 < x1 + width1 && y2 < y1 + height1) {
		return true;
	}
	if (x1 < x2 + width2 && y1 < y2 + height2) {
		return true;
	}
	if (x2 + width2 > x1 && y2 > y1 + height1) {
		return true;
	}
	if (x1 + width1 > x2 && y1 > y2 + height2) {
		return true;
	}
	return false;
}
