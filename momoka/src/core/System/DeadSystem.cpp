#include "stdafx.h"
#include "core/system/DeadSystem.h"
#include "core/GameCore.h"

void DeadSystem::Update(float& dt, GameCore& core) {
	//�����������ײ
	core.entityPool.Each<DeadComponent>(
		[&](GameEntityPool::Entity entity) {
		entity.Destory();
	});
}