#pragma once
#include "core/object/GameObjectPool.h"
class PropFactory {
public:
	GameEntityPool::Entity Create(GameEntityPool& pool, int i);
};
