#pragma once
#include "game/GameState.h"
#include "objects/Entity.h"
#include "objects/Hero.h"
#include "commands/Command.h"
#include "components/CollisionDetector.h"

#include <list>

class GameTestState : public GameState {
public:
	GameTestState();
	~GameTestState() override;

	void OnEnter() override;
	void OnExit() override;
	void Render(float dt) override;
	void Update() override;

private:
//	momoka::HandleTable<Entity*> m_handleTable_;
	std::list<int> m_actorList_;
	TileTpyeMap m_tileTypeMap_;
	TileMap m_tilesMap_;
	CollisionDetector m_collisionDetector_;

	Hero* m_pPlayerCharacter_;
	void WorldLoader();
	void GlobalPhysicsSimulation(Entity* entity);
	void EntityInit(Entity* entity);

	Command* m_commandW_;
	Command* m_commandA_;
	Command* m_commandS_;
	Command* m_commandD_;
};


