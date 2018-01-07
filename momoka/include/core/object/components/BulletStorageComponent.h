#pragma once
#include "core/object/components/Component.h"

#define maxGenreNum 10
#define normalbullet 0
#define longbullet 1
#define repelbullet 2
#define bomb 3

class BulletStorageComponent :public Component {
public:
	int MaxGenreNum = maxGenreNum;
	int curGenreNum = 0;
	int genre[maxGenreNum] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
	int storage[maxGenreNum] = { 100, 20, 10, 3, 10, 10, 10, 10 ,10 ,10 };
	int maxStorage[maxGenreNum] = { 100, 20, 10, 3, 10, 10, 10, 10 ,10 ,10 };
	int bulletCD[maxGenreNum] = { 0, 1, 3, 5, 1, 1, 1, 1, 1, 1 };
	float BulletCurCoolDown[maxGenreNum] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};