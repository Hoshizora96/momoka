#include "stdafx.h"
#include "core/factory/BulletFactory.h"

GameEntityPool::Entity BulletFactory::Create(GameEntityPool& pool, int curGenreNum) {
	auto positionCom = PositionComponent();
	positionCom.x = 0;
	positionCom.y = 0;


	auto velocityCom = VelocityComponent();
	velocityCom.vx = 0;
	velocityCom.vy = 0;


	auto moveCom = MoveComponent();
	moveCom.runningVelocity = 550;

	auto bulletCom = BulletComponent();

	auto hurtCom = HealthComponent();

	auto obstacleCom = ObstacleComponent();

	auto friendCom = FriendComponent();

	auto timingCom = TimingComponent();

	switch (curGenreNum) {
	case 0:
		velocityCom.vx = 700;
		velocityCom.vy = 0;
		bulletCom.obstacleWidth = momoka::BULLET_SIZE;
		bulletCom.obstacleHeight = momoka::BULLET_SIZE;
		bulletCom.damage = 10;
		bulletCom.MaxFlyTime = 2;
		break;
	case 1:
		velocityCom.vx = 550;
		velocityCom.vy = 0;
		bulletCom.obstacleWidth = 4 * momoka::BULLET_SIZE;
		bulletCom.obstacleHeight = 2 * momoka::BULLET_SIZE;
		bulletCom.damage = 20;
		bulletCom.MaxFlyTime = 3;
		break;
	default:
		break;
	}

	hurtCom.height = bulletCom.obstacleHeight;
	hurtCom.width = bulletCom.obstacleWidth;

	obstacleCom.obstacleHeight = bulletCom.obstacleHeight;
	obstacleCom.obstacleWidth = bulletCom.obstacleWidth;

	auto renderCom = RenderComponent();
	renderCom.renderHeight = obstacleCom.obstacleHeight;
	renderCom.renderWidth = obstacleCom.obstacleWidth;

	return pool.CreateEntity(
		positionCom,
		velocityCom,
		moveCom,
		obstacleCom,
		renderCom,
		bulletCom,
		hurtCom,
		timingCom,
		friendCom
		);
}
