#include "stdafx.h"
#include "core/system/BulletStorageControlSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"

void BulletStorageControlSystem::Update(float& dt) {
	auto& players = core->groupManager.GetGroup<groups::PlayerGroup>();
	auto bulletStorage = players[0].Get<BulletStorageComponent>();
		for (int i = 0;i < bulletStorage->MaxGenreNum;i++) {
			if (bulletStorage->BulletCurCoolDown[i] < bulletStorage->bulletCD[i]) {
				bulletStorage->BulletCurCoolDown[i] += dt;
			}
			else {
				bulletStorage->BulletCurCoolDown[i] = 0;
				if (bulletStorage->storage[i] < bulletStorage->maxStorage[i]) {
					bulletStorage->storage[i] += 1;
				}
			}
		}
}

std::string BulletStorageControlSystem::toString() {
	return std::string("bulletStorageControl system");
}