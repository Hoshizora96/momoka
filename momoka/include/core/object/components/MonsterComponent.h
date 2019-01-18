#pragma once
#include "core/object/components/Component.h"

class MonsterComponent :public Component {
public:
	float CollisionDamage = 10;
	bool isStatic = false;
};