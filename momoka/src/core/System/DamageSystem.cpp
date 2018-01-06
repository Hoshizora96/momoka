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
				player.Get<HealthComponent>()->healthPower -= monster.Get<MonsterComponent>()->CollisionDamage;
				if (player.Get<HealthComponent>()->healthPower <= 0) {
					player.Activate<DeadComponent>();
				}
			}
		});
	});



	core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, FriendComponent, BulletComponent>(
		[&](GameEntityPool::Entity playerbullet) {

		core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, MonsterComponent>(
				[&](GameEntityPool::Entity monster) {
			//�����ӵ��������ײ
			auto PlayerBullet = playerbullet.Get<VelocityComponent>();
			if (utility::CollisionDetector(
				Vector2F(playerbullet.Get<PositionComponent>()->x,
					playerbullet.Get<PositionComponent>()->y),
				Vector2F(playerbullet.Get<HealthComponent>()->width,
					playerbullet.Get<HealthComponent>()->height),
				Vector2F(monster.Get<PositionComponent>()->x,
					monster.Get<PositionComponent>()->y),
				Vector2F(monster.Get<HealthComponent>()->width,
					monster.Get<HealthComponent>()->height))) {
				playerbullet.Activate<DeadComponent>();
				monster.Get<HealthComponent>()->healthPower -= playerbullet.Get<BulletComponent>()->damage;
				if (monster.Get<HealthComponent>()->healthPower <= 0) {
					monster.Activate<DeadComponent>();
				}
			}
		});
	});

		core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, BulletComponent>(
			[&](GameEntityPool::Entity monsterbullet) {
			if (!monsterbullet.Has<FriendComponent>()) {
				core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, PlayerComponent>(
					[&](GameEntityPool::Entity player) {
					//����������ӵ���ײ
					if (utility::CollisionDetector(
						Vector2F(monsterbullet.Get<PositionComponent>()->x,
							monsterbullet.Get<PositionComponent>()->y),
						Vector2F(monsterbullet.Get<HealthComponent>()->width,
							monsterbullet.Get<HealthComponent>()->height),
						Vector2F(player.Get<PositionComponent>()->x,
							player.Get<PositionComponent>()->y),
						Vector2F(player.Get<HealthComponent>()->width,
							player.Get<HealthComponent>()->height))) {
						monsterbullet.Activate<DeadComponent>();
						player.Get<HealthComponent>()->healthPower -= monsterbullet.Get<BulletComponent>()->damage;
						if (player.Get<HealthComponent>()->healthPower <= 0) {
							player.Activate<DeadComponent>();
						}
					}
				});
			}
			
	});
}
