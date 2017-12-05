#include "stdafx.h"
#include "core/system/MoveSystem.h"
#include "core/GameCore.h"

void MoveSystem::Update(float& dt, GameCore& core) {
	core.entityPool.Each<VelocityComponent, PositionComponent>([&](GameEntityPool::Entity entity) {
		auto velocityComp = entity.Get<VelocityComponent>();
		auto positionComp = entity.Get<PositionComponent>();
		positionComp->x += velocityComp->vx * dt;
		positionComp->y += velocityComp->vy * dt;
	});
}
