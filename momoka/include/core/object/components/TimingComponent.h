#pragma once
#include "core/object/components/Component.h"

class TimingComponent :public Component {
public:
	float InputDisabledTime = 0;
	float MaxInputDisabledTime = 0.01;
	float BulletFlyingTime = 0;
};