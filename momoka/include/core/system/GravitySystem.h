#pragma once
#include "core/system/System.h"

class GravitySystem:public System {

public:
	void Update(float& dt) override;
};

