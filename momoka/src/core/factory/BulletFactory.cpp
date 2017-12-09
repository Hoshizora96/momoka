#include "stdafx.h"
#include "core/factory/BulletFactory.h"

GameEntityPool::Entity BulletFactory::Create(GameEntityPool& pool) {
	auto positionCom = PositionComponent();
	positionCom.x = 0;
	positionCom.y = 0;

	auto velocityCom = VelocityComponent();
	velocityCom.vx = 700;
	velocityCom.vy = 0;


	auto moveCom = MoveComponent();
	moveCom.runningVelocity = 700;

	auto bulletCom = BulletComponent();

	auto obstacleCom = ObstacleComponent();
	obstacleCom.obstacleHeight = bulletCom.obstacleHeight;
	obstacleCom.obstacleWidth = bulletCom.obstacleWidth;

	auto renderCom = RenderComponent();
	renderCom.renderHeight = obstacleCom.obstacleHeight;
	renderCom.renderWidth = obstacleCom.obstacleWidth;


	auto hurtCom = HurtComponent();
	hurtCom.height = bulletCom.obstacleHeight;
	hurtCom.width = bulletCom.obstacleWidth;

	

	auto timingCom = TimingComponent();

	return pool.CreateEntity(
		positionCom,
		velocityCom,
		moveCom,
		obstacleCom,
		renderCom,
		bulletCom,
		hurtCom,
		timingCom
		);
}
