#include "stdafx.h"
#include "core/system/CollisionSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"

void CollisionSystem::Update(float& dt, GameCore& core) {
	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent>([&](GameEntityPool::Entity player) { //人物与怪物碰撞
		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>([&](GameEntityPool::Entity monster) {
			auto Player = player.Get<VelocityComponent>();
			switch (utility::CollisionDetector(player.Get<PositionComponent>()->x,
				player.Get<PositionComponent>()->y,
				player.Get<HurtComponent>()->width,
				player.Get<HurtComponent>()->height,
				monster.Get<PositionComponent>()->x,
				monster.Get<PositionComponent>()->y,
				monster.Get<HurtComponent>()->width,
				monster.Get<HurtComponent>()->height)) {			
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
			switch (utility::CollisionDetector(playerbullet.Get<PositionComponent>()->x,
				playerbullet.Get<PositionComponent>()->y,
				playerbullet.Get<HurtComponent>()->width,
				playerbullet.Get<HurtComponent>()->height,
				monster.Get<PositionComponent>()->x,
				monster.Get<PositionComponent>()->y,
				monster.Get<HurtComponent>()->width,
				monster.Get<HurtComponent>()->height)) {
			case 0:
				break;
			case 1:
				playerbullet.Destory();
				monster.Get<HurtComponent>()->healthPower -= playerbullet.Get<BulletComponent>()->damage;
				if (monster.Get<HurtComponent>()->healthPower <= 0) {
					monster.Destory();
				}
				break;
			case 2:
				playerbullet.Destory();
				monster.Get<HurtComponent>()->healthPower -= playerbullet.Get<BulletComponent>()->damage;
				if (monster.Get<HurtComponent>()->healthPower <= 0) {
					monster.Destory();
				}
				break;
			default:
				break;
			}
		});
	});

	
}