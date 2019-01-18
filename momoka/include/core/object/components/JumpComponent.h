#pragma once
#include "core/object/components/Component.h"

class JumpComponent:public Component {
public:
	float jumpVelocity = 1000;
	float floatTime = 0;
	float maxFloatTime = 0.2;
	short jumpedTimes = 0;
	short maxJumpTimes = 2;
};