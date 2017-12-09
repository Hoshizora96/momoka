#pragma once
#include "core/system/System.h"

class CollisionSystem : public System {

public:
	void Update(float& dt, GameCore& core) override;
};