#include "stdafx.h"
#include "core/system/PlayerControlSystem.h"
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

				if (jumpCom->floatTime < jumpCom->maxFloatTime
					&& !(obstacleCom->yObstacle && obstacleCom->yDirection == Down)
					&& inputService->IsKeyEventHappened(DIK_K)) {
					velocityCom->vy = -jumpCom->jumpVelocity;
					jumpCom->floatTime += dt;
				}
				else if (inputService->IsKeyEventHappened(DIK_K, Key_release)) {
					if (jumpCom->floatTime < jumpCom->maxFloatTime)
						velocityCom->vy = 0;
					jumpCom->jumpedTimes++;
				}
			}

		}
	});
}
