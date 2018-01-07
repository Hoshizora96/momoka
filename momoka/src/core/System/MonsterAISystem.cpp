#include "stdafx.h"
#include "core/object/GameObjectPool.h"
#include "Engine.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/bahavior.h"
#include "core/factory/BulletFactory.h"
#include "core/system/MonsterAISystem.h"

void MonsterAISystem::Update(float& dt) {
	core->entityPool.Each<MonsterComponent>(
		[&](GameEntityPool::Entity monster) {
		if (monster.Has<InputControlComponent>()) {
			core->entityPool.Each<PlayerComponent>(
				[&](GameEntityPool::Entity player) {

				if (utility::CollisionDetector(
					Vector2F(player.Get<PositionComponent>()->x,
						player.Get<PositionComponent>()->y),
					Vector2F(player.Get<HealthComponent>()->width,
						player.Get<HealthComponent>()->height),
					Vector2F(monster.Get<PositionComponent>()->x - monster.Get<DetectAreaComponent>()->DetectWidth,
						monster.Get<PositionComponent>()->y - monster.Get<DetectAreaComponent>()->DetectHeight),
					Vector2F(2 * monster.Get<DetectAreaComponent>()->DetectWidth + monster.Get<HealthComponent>()->width,
						2 * monster.Get<DetectAreaComponent>()->DetectHeight + monster.Get<HealthComponent>()->height))
					) {
					auto MonsterJump = monster.Get<JumpComponent>();
					MonsterJump->maxJumpTimes = 1;
					MonsterJump->jumpVelocity = 500;
					MonsterJump->maxFloatTime = 0.15;
					behavior::Jump(monster, dt);
					if (player.Get<PositionComponent>()->x < monster.Get<PositionComponent>()->x) {
						monster.Get<MoveComponent>()->runningVelocity = 200;
						behavior::Running(monster, dt, Left);
						//behavior::Shoot(monster, core, Left);
					}
					else {
						monster.Get<MoveComponent>()->runningVelocity = 200;
						behavior::Running(monster, dt, Right);
						//behavior::Shoot(monster, core, Right);
					}
				}
				else {
					behavior::Stand(monster);
				}
			});
		}
		else {
			if (monster.Get<TimingComponent>()->InputDisabledTime < monster.Get<TimingComponent>()->MaxInputDisabledTime) {
				monster.Get<TimingComponent>()->InputDisabledTime += dt;
			}
			else {
				monster.Get<TimingComponent>()->InputDisabledTime = 0;
				monster.Activate<InputControlComponent>();
			}
		}
	});
}

std::string MonsterAISystem::toString() {
	return std::string("moster AI sytem");
}
