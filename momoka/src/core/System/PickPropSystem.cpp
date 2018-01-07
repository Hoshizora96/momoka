#include "stdafx.h"
#include "core/system/PickPropSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/prop.h"

/*
---------------------------------µÀ¾ßÁÐ±í----------------------------
0	ÑªÒ©£º»Ö¸´50%HP
1	
2 - 8	×Óµ¯
2	»÷ÍËµ¯
3	·¶Î§Õ¨µ¯
9	¹ÖÎïÍ£Ö¹Æ÷
*/

void PickPropSystem::Update(float& dt) {
	//ÈËÎïÓëµÀ¾ßÅö×²
	core->entityPool.Each<HealthComponent, PlayerComponent>(
		[&](GameEntityPool::Entity player) {

		core->entityPool.Each<PropComponent>(
			[&](GameEntityPool::Entity prop) {
			if (player.Has<HealthComponent>()) {
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
						break;
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
						prop::AddBullet(player, prop);
						prop.Activate<DeadComponent>();
						break;
					case 9:
						prop::AddProp(player, prop);
						prop.Activate<DeadComponent>();
						break;
					default:
						break;
					}
				}
			}
		});
	});

}

std::string PickPropSystem::toString() {
	return std::string("pickprop system");
}
