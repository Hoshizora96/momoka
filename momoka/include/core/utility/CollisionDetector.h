#pragma once

inline int CollisionDetector(float x1, float y1, float width1, float height1, float x2, float y2, float width2,
                       float height2) {
	if (x1 <= x2 && x2 <= x1 + width1 && y2 >= y1 && y2 <= y1 + height1) { //1������2������ײ
		return 1;
	}
	if (x1 >= x2 && x1 <= x2 + width2 && y1 >= y2 && y1 <= y2 + height2) { //1������2������ײ
		return 1;
	}
	if (x2 <= x1 && x1 <= x2 + width2 && y1 >= y2 && y1 <= y2 + height1) { //1������2������ײ
		return 2;
	}
	if (x2 >= x1 && x2 <= x1 + width1 && y2 >= y1 && y2 <= y1 + height1) { //1������2������ײ
		return 2;
	}
	return 0;
}
