#pragma once
#include "core/system/System.h"

class PickPropSystem : public System {

public:
	void Update(float& dt, GameCore& core) override;
};