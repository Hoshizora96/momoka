#pragma once
#include "core/system/System.h"

class DamageSystem : public System {

public:
	void Update(float& dt, GameCore& core) override;
};