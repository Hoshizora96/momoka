#include "stdafx.h"
#include "core/system/GravitySystem.h"
#include "core/GameCore.h"

void GravitySystem::Update(float& dt) {
	core->entityPool.Each<GravityComponent, VelocityComponent>([&](GameEntityPool::Entity entity) {
		auto gravityComp = entity.Get<GravityComponent>();
		auto velocityComp = entity.Get<VelocityComponent>();
		

		if (velocityComp->vy < gravityComp->maxFallingVelocity) {
			if (!(entity.Has<ObstacleComponent>()
				&& entity.Get<ObstacleComponent>()->yObstacle
				&& entity.Get<ObstacleComponent>()->yDirection == Down)) {
				if (entity.Has<BulletComponent>()) {
					if (entity.Get<BulletComponent>()->bulletType == 3) {
						velocityComp->vy += 300 * dt;
					}
				}
				velocityComp->vy += gravityComp->acceleration * dt;
			}
		}
		else {
			velocityComp->vy = gravityComp->maxFallingVelocity;
		}

	});
}

std::string GravitySystem::toString() {
	return std::string("gravity system");
}
