#include "stdafx.h"
#include "core/factory/MonsterFactory.h"

GameEntityPool::Entity MonsterFactory::Create(GameEntityPool& pool) {
	auto positionCom = PositionComponent();
	positionCom.x = 3 * momoka::TILE_SIZE;
	positionCom.y = 0;

	auto velocityCom = VelocityComponent();
	velocityCom.vx = 0;
	velocityCom.vy = 0;

	auto gravityCom = GravityComponent();

	auto jumpCom = JumpComponent();

	auto moveCom = MoveComponent();
	moveCom.runningVelocity = 500;

	auto obstacleCom = ObstacleComponent();
	obstacleCom.obstacleHeight = 2 * momoka::TILE_SIZE;
	obstacleCom.obstacleWidth = momoka::TILE_SIZE;

	auto renderCom = RenderComponent();
	renderCom.renderHeight = obstacleCom.obstacleHeight;
	renderCom.renderWidth = obstacleCom.obstacleWidth;

	auto monsterCom = MonsterComponent();

	auto hurtCom = HealthComponent();
	hurtCom.height = 2 * momoka::TILE_SIZE;
	hurtCom.width = momoka::TILE_SIZE;

	return pool.CreateEntity(
		positionCom,
		velocityCom,
		gravityCom,
		jumpCom,
		moveCom,
		obstacleCom,
		renderCom,
		monsterCom,
		hurtCom
		);
}