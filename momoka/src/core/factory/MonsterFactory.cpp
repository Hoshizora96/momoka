#include "stdafx.h"
#include "core/factory/MonsterFactory.h"

GameEntityPool::Entity MonsterFactory::Create(GameEntityPool& pool, int monsterIndex) {
	auto positionCom = PositionComponent();
	positionCom.x = 6 * momoka::TILE_SIZE;
	positionCom.y = 0;

	auto velocityCom = VelocityComponent();
	velocityCom.vx = 0;
	velocityCom.vy = 0;

	auto gravityCom = GravityComponent();

	auto bulletStorageCom = BulletStorageComponent();

	auto jumpCom = JumpComponent();

	auto inputControlCom = InputControlComponent();

	auto moveCom = MoveComponent();
	moveCom.runningVelocity = 500;

	auto obstacleCom = ObstacleComponent();
	obstacleCom.obstacleHeight = 2 * momoka::TILE_SIZE;
	obstacleCom.obstacleWidth = momoka::TILE_SIZE;

	auto renderCom = RenderComponent();
	renderCom.renderHeight = obstacleCom.obstacleHeight;
	renderCom.renderWidth = obstacleCom.obstacleWidth;

	auto monsterCom = MonsterComponent();

	auto timingCom = TimingComponent();

	auto DetectAreaCom = DetectAreaComponent();

	auto healthCom = HealthComponent();
	healthCom.height = 2 * momoka::TILE_SIZE;
	healthCom.width = momoka::TILE_SIZE;

	switch (monsterIndex) {
	case 0:
		obstacleCom.obstacleHeight = 2 * momoka::TILE_SIZE;
		obstacleCom.obstacleWidth = momoka::TILE_SIZE;
		monsterCom.CollisionDamage = 10;
		break;
	case 1:
		obstacleCom.obstacleHeight = 3 * momoka::TILE_SIZE;
		obstacleCom.obstacleWidth = 2 * momoka::TILE_SIZE;
		monsterCom.CollisionDamage = 20;
		break;
	default:
		break;
	}

	return pool.CreateEntity(
		positionCom,
		velocityCom,
		gravityCom,
		jumpCom,
		moveCom,
		obstacleCom,
		renderCom,
		monsterCom,
		healthCom,
		DetectAreaCom,
		bulletStorageCom,
		inputControlCom,
		timingCom
		);
}