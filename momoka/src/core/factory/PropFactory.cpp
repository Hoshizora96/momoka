#include "stdafx.h"
#include "core/factory/PropFactory.h"

GameEntityPool::Entity PropFactory::Create(GameEntityPool& pool, int propIndex) {
	auto positionCom = PositionComponent();
	positionCom.x = 0;
	positionCom.y = 0;

	auto velocityCom = VelocityComponent();
	velocityCom.vx = 0;
	velocityCom.vy = 0;

	auto moveCom = MoveComponent();
	moveCom.runningVelocity = 300;

	auto propCom = PropComponent();

	auto obstacleCom = ObstacleComponent();

	auto friendCom = FriendComponent();

	switch (propIndex) {
	case 0:
		positionCom.x = 5 * momoka::TILE_SIZE;
		positionCom.y = 0;
		propCom.PropIndex = 0;
		break;
	case 1:
		break;
	case 2:
		positionCom.x = 6 * momoka::TILE_SIZE;
		positionCom.y = momoka::TILE_SIZE;
		propCom.PropIndex = 2;
		break;
	default:
		break;
	}

	obstacleCom.obstacleHeight = propCom.Height;
	obstacleCom.obstacleWidth = propCom.Width;

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
		timingCom,
		friendCom,
		propCom
		);
}