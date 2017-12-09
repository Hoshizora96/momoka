#include "stdafx.h"
#include "core/system/DamageSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/bahavior.h"

void DamageSystem::Update(float& dt, GameCore& core) {
	//�����������ײ
	core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, PlayerComponent>(
		[&](GameEntityPool::Entity player) {

		core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, MonsterComponent>(
			[&](GameEntityPool::Entity monster) {

			auto playerVelocityCom = player.Get<VelocityComponent>();
			auto playerPositionCom = player.Get<PositionComponent>();
			auto monsterPositionCom = monster.Get<PositionComponent>();
			if (utility::CollisionDetector(
				Vector2F(player.Get<PositionComponent>()->x,
					player.Get<PositionComponent>()->y),
				Vector2F(player.Get<HealthComponent>()->width,
					player.Get<HealthComponent>()->height),
				Vector2F(monster.Get<PositionComponent>()->x,
					monster.Get<PositionComponent>()->y),
				Vector2F(monster.Get<HealthComponent>()->width,
					monster.Get<HealthComponent>()->height))
				) {
				player.Disable<InputControlComponent>();
				if (playerPositionCom->x < monsterPositionCom->x) {
					behavior::Repel(player, Left);
				}
				else {
					behavior::Repel(player, Right);
				}
			}

		});
	});



//	core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, PlayerComponent, BulletComponent>(
//		[&](GameEntityPool::Entity playerbullet) {
//
//		core.entityPool.Each<HurtComponent, VelocityComponent, PositionComponent, MonsterComponent>(
//			[&](GameEntityPool::Entity monster) {
//			//����������ӵ���ײ
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
