#pragma once
#include "core/object/GameObjectPool.h"
class HeroFactory {

public:
	GameEntityPool::Entity Create(GameEntityPool& pool);
};