#include "stdafx.h"
#include "core/system/CollisionSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"

void CollisionSystem::Update(float& dt, GameCore& core) {
	//人物与怪物碰撞
	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent>(
		[&](GameEntityPool::Entity player) {

		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>(
			[&](GameEntityPool::Entity monster) {

			auto playerVelocityCom = player.Get<VelocityComponent>();
			auto playerPositionCom = player.Get<PositionComponent>();
			auto monsterPositionCom = monster.Get<PositionComponent>();
			if (utility::CollisionDetector(
				Vector2F(player.Get<PositionComponent>()->x,
					player.Get<PositionComponent>()->y),
				Vector2F(player.Get<HurtComponent>()->width,
					player.Get<HurtComponent>()->height),
				Vector2F(monster.Get<PositionComponent>()->x,
					monster.Get<PositionComponent>()->y),
				Vector2F(monster.Get<HurtComponent>()->width,
					monster.Get<HurtComponent>()->height))
				) {
				player.Disable<CanInputComponent>();
				if (playerPositionCom->x < monsterPositionCom->x) {
					playerVelocityCom->vx = -500;
					playerVelocityCom->vy = -1000;
				}
				else {
					playerVelocityCom->vx = 500;
					playerVelocityCom->vy = -1000;
				}
			}

		});
	});

//	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent, BulletComponent>(
//		[&](GameEntityPool::Entity playerbullet) {
//
//		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>(
//			[&](GameEntityPool::Entity monster) {
//			//人物与怪物子弹碰撞
//			auto PlayerBullet = playerbullet.Get<VelocityComponent>();
//			if (utility::CollisionDetector(
//				Vector2F(player.Get<PositionComponent>()->x,
//					player.Get<PositionComponent>()->y),
//				Vector2F(player.Get<HurtComponent>()->width,
//					player.Get<HurtComponent>()->height),
//				Vector2F(monster.Get<PositionComponent>()->x,
//					monster.Get<PositionComponent>()->y),
//				Vector2F(monster.Get<HurtComponent>()->width,
//					monster.Get<HurtComponent>()->height))) {
//				playerbullet.Destory();
//				monster.Get<HurtComponent>()->healthPower -= playerbullet.Get<BulletComponent>()->damage;
//				if (monster.Get<HurtComponent>()->healthPower <= 0) {
//					monster.Destory();
//				}
//			}
//		});
//	});
}
