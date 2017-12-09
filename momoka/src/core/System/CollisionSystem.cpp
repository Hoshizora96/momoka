#include "stdafx.h"
#include "core/system/CollisionSystem.h"
#include "core/utility/CollisionDetector.h"
#include "core/GameCore.h"

void CollisionSystem::Update(float& dt, GameCore& core) {
	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent>([&](GameEntityPool::Entity player) { //人物与怪物碰撞
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

	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent, BulletComponent>([&](GameEntityPool::Entity playerbullet) {
		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>([&](GameEntityPool::Entity monster) { //人物与怪物子弹碰撞
			auto PlayerBullet = playerbullet.Get<VelocityComponent>();
			switch (CollisionDetector(playerbullet.Get<PositionComponent>()->x,
				playerbullet.Get<PositionComponent>()->y,
				playerbullet.Get<HurtComponent>()->Width,
				playerbullet.Get<HurtComponent>()->Height,
				monster.Get<PositionComponent>()->x,
				monster.Get<PositionComponent>()->y,
				monster.Get<HurtComponent>()->Width,
				monster.Get<HurtComponent>()->Height)) {
			case 0:
				break;
			case 1:
				playerbullet.Destory();
				monster.Get<HurtComponent>()->HealthPower -= playerbullet.Get<BulletComponent>()->damage;
				if (monster.Get<HurtComponent>()->HealthPower <= 0) {
					monster.Destory();
				}
				break;
			case 2:
				playerbullet.Destory();
				monster.Get<HurtComponent>()->HealthPower -= playerbullet.Get<BulletComponent>()->damage;
				if (monster.Get<HurtComponent>()->HealthPower <= 0) {
					monster.Destory();
				}
				break;
			default:
				break;
			}
		});
	});

	
}