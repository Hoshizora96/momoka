#include "stdafx.h"
#include "core/system/CollisionSystem.h"
#include "core/utility/CollisionDetector.h"
#include "core/GameCore.h"

void CollisionSystem::Update(float& dt, GameCore& core) {
	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent>([&](GameEntityPool::Entity player) {
		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>([&](GameEntityPool::Entity monster) {
			auto Player = player.Get<VelocityComponent>();
			switch (CollisionDetector(player.Get<PositionComponent>()->x,
				player.Get<PositionComponent>()->y,
				player.Get<HurtComponent>()->Width,
				player.Get<HurtComponent>()->Height,
				monster.Get<PositionComponent>()->x,
				monster.Get<PositionComponent>()->y,
				monster.Get<HurtComponent>()->Width,
				monster.Get<HurtComponent>()->Height)) {			
			case 0:
				break;
			case 1:	
				player.Disable<CanInputComponent>();
				Player->vx = -500;
				Player->vy = -1000;
				break;
			case 2:
				player.Disable<CanInputComponent>();
				Player->vx = 500;
				Player->vy = -1000;
				break;
			default:
				break;
			}
		});
	});
	/*core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>([&](GameEntityPool::Entity player) {
		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent>([&](GameEntityPool::Entity monster) {
			switch (CollisionDetector(player.Get<PositionComponent>()->x,
				player.Get<PositionComponent>()->y,
				player.Get<HurtComponent>()->Width,
				player.Get<HurtComponent>()->Height,
				monster.Get<PositionComponent>()->x,
				monster.Get<PositionComponent>()->y,
				monster.Get<HurtComponent>()->Width,
				monster.Get<HurtComponent>()->Height)) {
				auto Player = player.Get<VelocityComponent>();
			case 0:
				break;
			case 1:
				Player->vx = -100;
				Player->vy = -100;
				break;
			case 2:
				Player->vx = 100;
				Player->vy = -100;
				break;
			default:
				break;
			}
		});
	});*/
}