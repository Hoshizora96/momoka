#pragma once
#include "util/Vector2.h"

enum HITBOX_TYPE {
	Body,
	Attack
};

class HitBox {
public:
	Vector2<float> position;
	Vector2<float> size;

	HITBOX_TYPE type;
};
