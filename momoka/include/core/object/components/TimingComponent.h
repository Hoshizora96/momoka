#pragma once
#include "core/object/components/Component.h"

class TimingComponent :public Component {
public:
	float InputDisabledTime = 0;
	float MaxInputDisabledTime = 0.3;
	float ShootDisabledTime = 0;
	float ShootInterval = 0.8;
};