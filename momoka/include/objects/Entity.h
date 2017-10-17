#pragma once
#include "util/TileInfo.h"

class Entity {
public:
	virtual ~Entity();
	float GetX() const;
	float GetY() const;

	float GetCollisionWidth() const;
	float GetCollisionHeight() const;

	bool IsObstructive() const;
	bool HasGravity() const;

	virtual void Update();
	virtual void Render(float dt);

	void SetX(float x);
	void SetY(float y);

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveUp();
	virtual void MoveDown();
	virtual void Jump();

	virtual void Onland();

	virtual bool TakeTileCollision(momoka_global::COLLISION_FLAG flag, TileInfo tileInfo);
	
	void ClearObstructFlags();

	float GetVelocityX() const;
	float GetVelocityY() const;

	void SetVelocityX(float velocityX);
	void SetVelocityY(float velocityY);

	void SetOnLandFlag(bool flag);

protected:
	// 碰撞标志，false代表不会发生碰撞，这里的碰撞指的是与障碍物碰撞
	bool m_isObstructive_;
	bool m_hasGravity_;

	bool m_leftObstructFlag_;
	bool m_rightObstructFlag_;
	bool m_upObstructFlag_;
	bool m_downObstructFlag_;

	bool m_isOnLand_;

	float m_posX_;
	float m_posY_;

	float m_collisionWidth_;
	float m_collisionHeight_;

	float m_velocityX_;
	float m_velocityY_;

};
