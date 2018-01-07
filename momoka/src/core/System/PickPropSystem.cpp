#include "stdafx.h"
#include "core/system/PickPropSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/prop.h"

/*
---------------------------------�����б�----------------------------
0	Ѫҩ���ָ�50%HP
1	
2 - 8	�ӵ�
2	���˵�
3	��Χը��
*/

void PickPropSystem::Update(float& dt) {
	//�����������ײ
	core->entityPool.Each<HealthComponent, PlayerComponent>(
		[&](GameEntityPool::Entity player) {

		core->entityPool.Each<PropComponent>(
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
					prop::AddProp(player, prop);
					prop.Activate<DeadComponent>();
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
				default:
					break;
				}
			}
		});
	});

}

std::string PickPropSystem::toString() {
	return std::string("pickprop system");
}
