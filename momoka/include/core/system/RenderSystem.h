#pragma once
#include "core/system/System.h"
#include "core/object/GameObjectPool.h"

class RenderSystem:public System {
	void PlayAnimation(GameEntityPool::Entity& entity, float dt);
public:
	void Update(float& dt) override;
	std::string toString() override;
};
