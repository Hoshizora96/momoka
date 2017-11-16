#pragma once
#include "objects/Entity.h"
#include "map/World.h"
class HeroState;
class World;
class Hero : public Entity {
public:
	~Hero() override;
	explicit Hero(World& world);
	void Update(float dt) override;
	void Render(float dt) override;

	int GetJumpNum() const;
	void SetJumpNum(int);

	bool LoadConfig(char* path) override;

private:
	void HandleInput();
	bool SwitchState(HeroState* state);

	void HandleCollisionInfo(CollisionInfo info) override;
	
	HeroState* m_state_;
	int m_jumpnumber_;
	World& m_world_;
};
