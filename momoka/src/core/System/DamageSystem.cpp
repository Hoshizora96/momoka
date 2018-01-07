#include "stdafx.h"
#include "core/system/DamageSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/bahavior.h"

void DamageSystem::Update(float& dt) {

	auto& players = core->groupManager.GetGroup<groups::PlayerGroup>();
	auto& monsters = core->groupManager.GetGroup<groups::MonsterGroup>();

	for(int i = 0; i < players.Size(); i++) {
		auto player = players[i];
		for(int j = 0; j < monsters.Size(); j++) {			
			auto monster = monsters[j];
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
		}
	}

	auto& friendBullets = core->groupManager.GetGroup<groups::FriendBulletGroup>();
	for(int i = 0; i < friendBullets.Size(); i++) {
		auto playerbullet = friendBullets[i];
		if (playerbullet.Get<TimingComponent>()->BulletFlyingTime < playerbullet.Get<BulletComponent>()->MaxFlyTime) {
			playerbullet.Get<TimingComponent>()->BulletFlyingTime += dt;
		}
		else {
			playerbullet.Activate<DeadComponent>();
		}
		for(int j = 0; j < monsters.Size(); j++) {
			auto monster = monsters[j];

			if (utility::CollisionDetector(
				Vector2F(playerbullet.Get<PositionComponent>()->x,
					playerbullet.Get<PositionComponent>()->y),
				Vector2F(playerbullet.Get<HealthComponent>()->width,
					playerbullet.Get<HealthComponent>()->height),
				Vector2F(monster.Get<PositionComponent>()->x,
					monster.Get<PositionComponent>()->y),
				Vector2F(monster.Get<HealthComponent>()->width,
					monster.Get<HealthComponent>()->height))) {
				if (playerbullet.Get<BulletComponent>()->bulletType == 2) { //击退弹的效果
					monster.Disable<InputControlComponent>();
					if (playerbullet.Get<PositionComponent>()->x > monster.Get<PositionComponent>()->x) {
						behavior::Repel(monster, Left);
					}
					else {
						behavior::Repel(monster, Right);
					}
				}
				if (playerbullet.Get<BulletComponent>()->bulletType == 3) { //范围炸弹的效果
					for (int j = 0; j < monsters.Size(); j++) {
						auto monster = monsters[j];
						if (utility::CollisionDetector(
							Vector2F(playerbullet.Get<PositionComponent>()->x + playerbullet.Get<BulletComponent>()->explosionRange,
								playerbullet.Get<PositionComponent>()->y + playerbullet.Get<BulletComponent>()->explosionRange),
							Vector2F(playerbullet.Get<HealthComponent>()->width,
								playerbullet.Get<HealthComponent>()->height),
							Vector2F(monster.Get<PositionComponent>()->x,
								monster.Get<PositionComponent>()->y),
							Vector2F(monster.Get<HealthComponent>()->width,
								monster.Get<HealthComponent>()->height))) {

						}
						monster.Disable<InputControlComponent>();
						if (playerbullet.Get<PositionComponent>()->x > monster.Get<PositionComponent>()->x) {
							behavior::Repel(monster, Left);
						}
						else {
							behavior::Repel(monster, Right);
						}
					}
				}
				playerbullet.Activate<DeadComponent>();
				monster.Get<HealthComponent>()->healthPower -= playerbullet.Get<BulletComponent>()->damage;
				if (monster.Get<HealthComponent>()->healthPower <= 0) {
					monster.Activate<DeadComponent>();
				}
			}
		}
	}

}

std::string DamageSystem::toString() {
	return std::string("damage system");
}

