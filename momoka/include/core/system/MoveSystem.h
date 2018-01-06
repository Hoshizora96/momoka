#pragma once
#include "core/system/System.h"

class MoveSystem : public System {

public:
	void Update(float& dt) override;
	std::string toString() override;
};
