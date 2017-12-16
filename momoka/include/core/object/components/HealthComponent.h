#pragma once
#pragma once
#include "core/object/components/Component.h"

class HealthComponent :public Component {
public:
	float healthPower = 100;
	float width = 0;
	float height = 0;
};