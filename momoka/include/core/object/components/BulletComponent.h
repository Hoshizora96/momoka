#pragma once
#include "core/object/components/Component.h"

class BulletComponent :public Component {
public:
	float obstacleHeight = momoka::BULLET_SIZE;
	float obstacleWidth = momoka::BULLET_SIZE;
	float damage = 2 * momoka::DAMAGE_UNIT;
};