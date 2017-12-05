#pragma once
#include "core/object/GameObjectPool.h"

class Factory {
public:
	virtual ~Factory() = default;
	virtual GameEntityPool::Entity Create(GameEntityPool& pool) = 0;
};