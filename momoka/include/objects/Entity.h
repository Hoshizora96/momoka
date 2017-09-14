#pragma once

class Entity {
public:
	virtual ~Entity() = default;
	virtual float GetX();
	virtual float GetY();

	virtual bool OnEvent();

	virtual float GetVelocityX();
	virtual float GetVelocityY();

	virtual float GetCollisionWidth();
	virtual float GetCollisionHeight();

	virtual bool IsObstructive();

	virtual bool PlayerControlHandle();

	virtual bool Update(float dt);
	virtual bool Render();

protected:
	// 碰撞标志，false代表不会发生碰撞，这里的碰撞指的是与障碍物碰撞
	bool m_isObstructive_;

	bool m_leftObstructFlag_;
	bool m_rightObstructFlag_;
	bool m_upObstructFlag_;
	bool m_downObstructFlag_;

	float m_posX_;
	float m_posY_;

	float m_velocityX_;
	float m_velocityY_;

	float m_collisionWidth_;
	float m_collisionHeight_;

};
