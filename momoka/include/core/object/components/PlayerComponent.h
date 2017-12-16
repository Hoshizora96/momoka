#pragma once
#include "core/object/components/Component.h"

class PlayerComponent:public Component {
public:
	DIRECTION direction = DIRECTION::Left;
};