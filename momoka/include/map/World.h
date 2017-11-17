#pragma once
#include "mixin/Renderable.h"
#include "mixin/Updatable.h"
#include "objects/GameObject.h"
#include "objects/Entity.h"
#include "components/Camera.h"
#include "components/CollisionDetector.h"
#include "map/TileSet.h"
#include "objects/Hero.h"

class Hero;
class World : public Renderable, public Updatable {

public:
	World();

	void Render(Camera* camera = nullptr) override;
	void Update(float dt) override;
	CollisionDetector& GetCollisionDetector() const;

	bool LoadConfig(char* path);

	Camera* GetCamera() const;

private:
	TileSet* m_pTileSet_;
	CollisionDetector* m_pCollisionDetector_;
	Hero* m_pHero_;
	Camera* m_pCamera_;
};
