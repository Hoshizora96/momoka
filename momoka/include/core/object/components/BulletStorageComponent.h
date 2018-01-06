#pragma once
#include "core/object/components/Component.h"

#define maxGenreNum 10
#define normalbullet 0
#define longbullet 1

class BulletStorageComponent :public Component {
public:
	int MaxGenreNum = maxGenreNum;
	int curGenreNum = 0;
	int genre[maxGenreNum] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
};