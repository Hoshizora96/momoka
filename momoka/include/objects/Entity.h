#pragma once
#include "mixin/Renderable.h"
#include "components/PhysicalBody.h"
#include "objects/GameObject.h"
#include "util/Vector2.h"
#include "components/CollisionInfo.h"

class Entity : public GameObject, public Renderable {
public:
	~Entity() override;
	Entity();
	
	void Update(float dt) override;
	virtual void Render(float dt, Camera* camera = nullptr) override;

	virtual bool LoadConfig(char* path);

	Vector2<float> GetVelocity();
	Vector2<float> GetPosition();
	float GetMovingVelocity();

	// ���������ܵ����öˣ�������Щ��������X��Yֵ�ĺ������ն����������
	// �����Ҫ������ƣ�ֻҪoverride���������������оͿ�����
	virtual void SetVelocity(float vx, float vy);
	virtual void SetPosition(float x, float y);
	virtual void SetMovingVelocity(float velocity);

	float GetVelocityX();
	float GetVelocityY();
	void SetVelocityX(float vx);
	void SetVelocityY(float vy);

	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);

protected:
	virtual void HandleCollisionInfo(CollisionInfo info);
	PhysicalBody m_physicalBody_;
};
