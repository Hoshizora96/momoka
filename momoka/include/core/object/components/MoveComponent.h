#pragma once
#include "core/object/components/Component.h"

class MoveComponent:public Component {
public:
	float runningVelocity = 1000;
};