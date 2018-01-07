#pragma once
#include "core/object/components/Component.h"

class BulletComponent :public Component {
public:
	int bulletType = 0;
	float obstacleHeight = momoka::BULLET_SIZE;
	float obstacleWidth = momoka::BULLET_SIZE;
	float damage = 2 * momoka::DAMAGE_UNIT;
	float MaxFlyTime = 3;
	float explosionRange = 6 * momoka::TILE_SIZE;
};