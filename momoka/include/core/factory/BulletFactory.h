#pragma once
#include "core/object/GameObjectPool.h"
class BulletFactory{
public:
	GameEntityPool::Entity Create(GameEntityPool& pool);
};
