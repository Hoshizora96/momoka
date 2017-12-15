#include "stdafx.h"
#include "core/system/PickPropSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/prop.h"

void PickPropSystem::Update(float& dt, GameCore& core) {
	//人物与道具碰撞
	core.entityPool.Each<HealthComponent, PlayerComponent>(
		[&](GameEntityPool::Entity player) {

		core.entityPool.Each<PropComponent>(
			[&](GameEntityPool::Entity prop) {
			if (utility::CollisionDetector(
				Vector2F(player.Get<PositionComponent>()->x,
					player.Get<PositionComponent>()->y),
				Vector2F(player.Get<HealthComponent>()->width,
					player.Get<HealthComponent>()->height),
				Vector2F(prop.Get<PositionComponent>()->x,
					prop.Get<PositionComponent>()->y),
				Vector2F(prop.Get<PropComponent>()->Width,
					prop.Get<PropComponent>()->Height))
				) {
				switch (prop.Get<PropComponent>()->PropIndex) {
				case 0:
					prop::Recover(player, prop);
					prop.Activate<DeadComponent>();
					break;
				case 1:
				case 2:
				case 3:
					prop::AddBullet(player, prop);
					prop.Activate<DeadComponent>();
					break;
				default:
					break;
				}
			}
		});
	});

}