#pragma once
#include "core/object/components/Component.h"

#define normalbullet 0
#define longbullet 0

class BulletStorageComponent :public Component {
public:
	int maxGenreNum = 10;
	int curGenreNum = 0;
	int genre[10] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
};