#pragma once
#include "core/object/components/Component.h"

class PropComponent :public Component {
public:
	int PropIndex = -1;
	float Width = momoka::TILE_SIZE / 4;
	float Height = momoka::TILE_SIZE / 4;
	float Recovery = 50;
};