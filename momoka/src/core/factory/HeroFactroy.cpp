#include "stdafx.h"
#include "core/factory/HeroFactory.h"

GameEntityPool::Entity HeroFactory::Create(GameEntityPool& pool) {
	auto positionCom = PositionComponent();
	positionCom.x = 0;
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

	auto playerCom = PlayerComponent();

	return pool.CreateEntity(
		positionCom,
		velocityCom,
		gravityCom,
		jumpCom,
		moveCom,
		obstacleCom,
		renderCom,
		playerCom
	);
}
