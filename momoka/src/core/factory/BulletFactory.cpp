#include "stdafx.h"
#include "core/factory/BulletFactory.h"

GameEntityPool::Entity BulletFactory::Create(GameEntityPool& pool) {
	return pool.CreateEntity();
}
