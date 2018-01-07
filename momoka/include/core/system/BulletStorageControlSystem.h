#pragma once
#include "core/system/System.h"
#include "core/object/GameObjectPool.h"

class BulletStorageControlSystem : public System {

public:
	void Update(float& dt) override;
	std::string toString() override;
};
