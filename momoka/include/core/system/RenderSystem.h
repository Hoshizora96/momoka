#pragma once
#include "core/system/System.h"

class RenderSystem:public System {

public:
	void Update(float& dt) override;
	std::string toString() override;
};