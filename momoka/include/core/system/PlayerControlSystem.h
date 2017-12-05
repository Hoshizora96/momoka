#pragma once
#include "core/system/System.h"

class PlayerControlSystem:public System {

public:
	void Update(float& dt, GameCore& core) override;
};