#pragma once
#include "core/object/components/Component.h"
#include "global.h"

class DetectAreaComponent :public Component {
public:
	float DetectWidth = 4 * momoka::TILE_SIZE;
	float DetectHeight = 3 * momoka::TILE_SIZE;
};