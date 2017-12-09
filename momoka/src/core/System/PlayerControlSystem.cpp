#include "stdafx.h"
#include "core/system/PlayerControlSystem.h"
#include "core/factory/BulletFactory.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/InputService.h"
#include "util/Log.h"

void PlayerControlSystem::Update(float& dt, GameCore& core) {
	auto inputService = Engine::serviceLoader.LocateService<InputService>(Service_input).lock();
	core.entityPool.Each<
		PlayerComponent,
		VelocityComponent,
		MoveComponent
	>([&](GameEntityPool::Entity entity) {
		auto velocityCom = entity.Get<VelocityComponent>();
		if (entity.Has<CanInputComponent>()) {		
			if (inputService->IsKeyEventHappened(DIK_D)) {
				velocityCom->vx = entity.Get<MoveComponent>()->runningVelocity;
			}
			else if (inputService->IsKeyEventHappened(DIK_D, Key_release)) {
				velocityCom->vx = 0;
			}

			if (inputService->IsKeyEventHappened(DIK_A)) {
				velocityCom->vx = -entity.Get<MoveComponent>()->runningVelocity;
			}
			else if (inputService->IsKeyEventHappened(DIK_A, Key_release)) {
				velocityCom->vx = 0;
			}

			if (entity.Has<ObstacleComponent, JumpComponent>()) {
				auto jumpCom = entity.Get<JumpComponent>();
				auto obstacleCom = entity.Get<ObstacleComponent>();

			if (obstacleCom->yObstacle && obstacleCom->yDirection == Down) {
				jumpCom->jumpedTimes = 0;
				jumpCom->floatTime = 0;
			}
			if (jumpCom->jumpedTimes < jumpCom->maxJumpTimes) {
				if (inputService->IsKeyEventHappened(DIK_K, Key_press)) {
					jumpCom->floatTime = 0;
					velocityCom->vy = -jumpCom->jumpVelocity;
				}

				if (jumpCom->jumpedTimes <= jumpCom->maxJumpTimes
					&& jumpCom->floatTime < jumpCom->maxFloatTime
					&& !(obstacleCom->yObstacle && obstacleCom->yDirection == Down)
					&& inputService->IsKeyEventHappened(DIK_K)) {
					velocityCom->vy = -jumpCom->jumpVelocity;
					jumpCom->floatTime += dt;
				}
				else if (jumpCom->floatTime < jumpCom->maxFloatTime
					&& inputService->IsKeyEventHappened(DIK_K, Key_release)) {
					velocityCom->vy = 0;
				}
			}

			if (entity.Has<BulletStorageComponent>()) {
				if (inputService->IsKeyEventHappened(DIK_J, Key_press)) { //Éä»÷
					BulletFactory bulletFactory;
					auto bullet = bulletFactory.Create(core.entityPool);
					bullet.Get<PositionComponent>()->x = entity.Get<PositionComponent>()->x + momoka::TILE_SIZE;
					bullet.Get<PositionComponent>()->y = entity.Get<PositionComponent>()->y + momoka::TILE_SIZE;				}
			}
		}
		else {

			
			if (entity.Has<TimingComponent>()) {
				auto inputableTime = entity.Get<TimingComponent>();
				if (inputableTime->InputDisabledTime < inputableTime->MaxInputDisabledTime) {
					inputableTime->InputDisabledTime += dt;
				}
				else {
					inputableTime->InputDisabledTime = 0;
					if (entity.Get<ObstacleComponent>()->yObstacle && entity.Get<ObstacleComponent>()->yDirection == Down) {
						entity.Get<VelocityComponent>()->vx = 0;
						entity.Get<VelocityComponent>()->vy = 0;
						entity.Activate<CanInputComponent>();
					}
				}
			}
		}

	});
}
