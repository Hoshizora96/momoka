#pragma once
#pragma once
#include "core/object/components/Component.h"

class HurtComponent :public Component {
public:
	float HealthPower = 100;
	float Width = 0;
	float Height = 0;
};