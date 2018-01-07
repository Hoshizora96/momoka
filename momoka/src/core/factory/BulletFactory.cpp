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

	switch (curGenreNum) {
	case 0:
		velocityCom.vx = 600;
		velocityCom.vy = 0;
		bulletCom.obstacleWidth = momoka::BULLET_SIZE;
		bulletCom.obstacleHeight = momoka::BULLET_SIZE;
		bulletCom.damage = 20;
		bulletCom.MaxFlyTime = 2;
		bulletCom.bulletType = 0;
		break;
	case 1:
		velocityCom.vx = 500;
		velocityCom.vy = 0;
		bulletCom.obstacleWidth = 4 * momoka::BULLET_SIZE;
		bulletCom.obstacleHeight = 2 * momoka::BULLET_SIZE;
		bulletCom.damage = 30;
		bulletCom.MaxFlyTime = 3;
		bulletCom.bulletType = 1;
		break;
	case 2:
		velocityCom.vx = 700;
		velocityCom.vy = 0;
		bulletCom.obstacleWidth = 2 * momoka::BULLET_SIZE;
		bulletCom.obstacleHeight = 1.5 * momoka::BULLET_SIZE;
		bulletCom.damage = 10;
		bulletCom.MaxFlyTime = 2;
		bulletCom.bulletType = 2;
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

	auto timingCom = TimingComponent();

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
