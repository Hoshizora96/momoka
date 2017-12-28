#pragma once
#include "core/system/System.h"

class DeadSystem : public System {

public:
	void Update(float& dt) override;
};