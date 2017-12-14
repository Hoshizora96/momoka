#include "stdafx.h"
#include "core/system/DeadSystem.h"
#include "core/GameCore.h"

void DeadSystem::Update(float& dt, GameCore& core) {
	//人物与怪物碰撞
	core.entityPool.Each<DeadComponent>(
		[&](GameEntityPool::Entity entity) {
		entity.Destory();
	});
}