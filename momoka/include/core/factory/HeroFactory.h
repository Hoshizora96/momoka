#pragma once
#include "core/factory/Factory.h"
class HeroFactroy : public Factory {

public:
	GameEntityPool::Entity Create(GameEntityPool& pool) override;

};