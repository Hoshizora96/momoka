#pragma once
#include "System.h"
class GuiSystem:public System {

public:
	void Update(float& dt) override;
	std::string toString() override;
};