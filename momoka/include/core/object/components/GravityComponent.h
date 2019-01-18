#pragma once
#include "core/object/components/Component.h"

class GravityComponent : public Component {
public:
	float acceleration = 15000;
	float maxFallingVelocity = 1000;
};
