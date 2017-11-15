#pragma once
#include "mixin/Renderable.h"
#include "components/PhysicalBody.h"
#include "objects/GameObject.h"
#include "util/Vector2.h"
#include "components/CollisionInfo.h"

class Entity : public GameObject, public Renderable {
public:
	PhysicalBody physicalBody;

	~Entity() override;
	Entity();
	// ������������Ӧ���Ǵ��ⲿ���õ�
	void Update(float dt) override;
	void Render(float dt) override;

	virtual bool LoadConfig(char* path);

private:
	virtual void HandleCollisionInfo(CollisionInfo info);
};
