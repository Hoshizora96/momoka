#include "stdafx.h"
#include "core/system/DamageSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/bahavior.h"

void DamageSystem::Update(float& dt, GameCore& core) {
	LONGLONG begin = 0, end = 0;

	//人物与怪物碰撞
	begin = GetCurrentTick();
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
	end = GetCurrentTick();

//	if (Engine::aSecond) {
//		MOMOKA_LOG(momoka::debug) << " +-- first loop cost " << (end - begin) * 1000 / Engine::freq;
//	}


	core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, FriendComponent, BulletComponent>(
		[&](GameEntityPool::Entity playerbullet) {

		core.entityPool.Each<HealthComponent, VelocityComponent, PositionComponent, MonsterComponent>(
				[&](GameEntityPool::Entity monster) {
			//人物与怪物子弹碰撞
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
	end = GetCurrentTick();

//	if(Engine::aSecond) {
//		MOMOKA_LOG(momoka::debug) << " +-- second loop cost " << (end - begin) * 1000 / Engine::freq;
//	}
	
}
