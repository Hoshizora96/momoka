#pragma once
#include "core/object/GameObjectPool.h"
class MonsterFactory {

public:
	GameEntityPool::Entity Create(GameEntityPool& pool);
}; 