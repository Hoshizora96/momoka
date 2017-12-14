#pragma once
#include "core/object/GameObjectPool.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/InputService.h"
#include "core/factory/PropFactory.h"

namespace prop {
	inline void Recover(GameEntityPool::Entity& player, GameEntityPool::Entity& prop) {
		if (player.Get<HealthComponent>()->healthPower + prop.Get<PropComponent>()->Recovery > 100) {
			player.Get<HealthComponent>()->healthPower = 100;
		}
		else {
			player.Get<HealthComponent>()->healthPower += prop.Get<PropComponent>()->Recovery;
		}
	}
}