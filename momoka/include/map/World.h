#pragma once
#include "mixin/Renderable.h"
#include "mixin/Updatable.h"
#include "objects/GameObject.h"
#include "objects/Entity.h"
#include "components/CollisionDetector.h"
#include "map/TileSet.h"
#include "objects/Hero.h"

class Hero;
class World : public Renderable, public Updatable {

public:
	World();

	void Render(float dt) override;
	void Update(float dt) override;
	CollisionDetector& GetCollisionDetector() const;

	bool LoadConfig(char* path);

private:
	TileSet* m_pTileSet_;
	CollisionDetector* m_pCollisionDetector_;
	Hero* m_pHero_;
};
