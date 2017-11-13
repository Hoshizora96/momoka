#pragma once
#include "mixin/Renderable.h"
#include "components/PhysicalBody.h"
#include "objects/GameObject.h"
#include "mixin/Collidable.h"
#include "util/Vector2.h"

class Entity : public GameObject, public Renderable, public Collidable {
public:
	~Entity() override;
	// 这三个函数都应该是从外部调用的
	void Update(float dt) override;
	void Render(float dt) override;
	void HandleCollision(const CollisionDetector& collisionDetector) override;
protected:
	PhysicalBody m_physicalBody_;
};
