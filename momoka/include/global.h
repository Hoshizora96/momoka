#pragma once

enum SERVICE_TYPE { Service_input, Service_graphic };

enum COLLISION_FLAG { Collision_left, Collision_right, Collision_up, Collision_down };

enum KEY_HERO { Key_left, Key_right, Key_up, Key_down, Key_jump, Key_nothing };

static const float REFRESH_RATE = 60.F;
static const int TILE_SIZE = 60;
static const __int64 MULX = 1000000;
