#pragma once
#include "global.h"
#include "components/PhysicalBody.h"
#include "elements/tile.h"
#include "components/CollisionDetector.h"

class Entity {
public:
	
	virtual ~Entity();
	float GetX() const;
	float GetY() const;

	void SetCollisionDetector(CollisionDetector* pCollisionDetector);

	virtual void Update();
	virtual void Render(float dt);

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveUp();
	virtual void MoveDown();
	virtual void Jump();

	virtual void HandleInput();

	virtual void Onland();

	void SetX(float velocityX);
	void SetY(float velocityY);
	

	float GetVelocityX() const;
	float GetVelocityY() const;

	void SetVelocityX(float velocityX);
	void SetVelocityY(float velocityY);

	void SetOnLandFlag(bool flag);

protected:
	PhysicalBody m_physicalBody_;
	PhysicalBody m_nextFramePhysicalBody_;

	bool m_isOnLand_;

	CollisionDetector* m_pCollisionDetector_;

};
