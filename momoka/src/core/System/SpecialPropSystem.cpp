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
		switch (useRequest) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
	});
}

std::string SpecialPropSystem::toString() {
	return std::string("specialprop system");
}