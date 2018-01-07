#include "stdafx.h"
#include "core/system/SpecialPropSystem.h"
#include "core/utility/utility.h"
#include "core/GameCore.h"
#include "core/utility/prop.h"

void SpecialPropSystem::Update(float& dt) {
	core->entityPool.Each<HealthComponent, PlayerComponent>(
		[&](GameEntityPool::Entity player) {
		auto PropStorageCom = player.Get<PropStorageComponent>();
		int useRequest = PropStorageCom->useRequest;
		auto& monsters = core->groupManager.GetGroup<groups::MonsterGroup>();
		switch (useRequest) {
		case 0:
			if (PropStorageCom->PropStorage[0] <= 0)
				break;
			PropStorageCom->PropStorage[0] -= 1;
			for (int i = 0;i < monsters.Size();i++) {
				monsters[i].Disable<InputControlComponent>();
				monsters[i].Get<VelocityComponent>()->vx = 0;
				monsters[i].Get<VelocityComponent>()->vy = 0;
				monsters[i].Get<MonsterComponent>()->isStatic = true;
				monsters[i].Disable<HealthComponent>();
			}
			useRequest = -1;
			break;
		case 1:
			useRequest = -1;
			break;
		case 2:
			useRequest = -1;
			break;
		default:
			break;
			
		}
	});
}

std::string SpecialPropSystem::toString() {
	return std::string("specialprop system");
}