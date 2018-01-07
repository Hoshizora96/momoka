#include "stdafx.h"
#include "core/system/PlayerControlSystem.h"
#include "core/factory/BulletFactory.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/InputService.h"
#include "util/Log.h"
#include "core/utility/bahavior.h"

void PlayerControlSystem::Update(float& dt) {
	auto inputService = Engine::serviceLoader.LocateService<InputService>(Service_input).lock();
	core->entityPool.Each<
		PlayerComponent,
		VelocityComponent,
		MoveComponent,
		PositionComponent
	>([&](GameEntityPool::Entity entity) {
		auto velocityCom = entity.Get<VelocityComponent>();
		auto playerCom = entity.Get<PlayerComponent>();
		if (entity.Has<InputControlComponent>()) {
			if (inputService->IsKeyEventHappened(DIK_D)) {
				behavior::Running(entity, dt, Right);
				if(!playerCom->isBacking)
					playerCom->direction = Right;
			}
			else if (inputService->IsKeyEventHappened(DIK_A)) {
				behavior::Running(entity, dt, Left);
				if (!playerCom->isBacking)
					playerCom->direction = Left;
			}
			else {
				behavior::Stand(entity);
			}

			if (inputService->IsKeyEventHappened(DIK_K)) {
				behavior::Jump(entity, dt);
			}
			else if (inputService->IsKeyEventHappened(DIK_K, Key_release)) {
				behavior::StopJumpAndFall(entity);
			}

			if (inputService->IsKeyEventHappened(DIK_LSHIFT, Key_down)) {
				playerCom->isBacking = true;
			}

			if (inputService->IsKeyEventHappened(DIK_LSHIFT, Key_release)) {
				playerCom->isBacking = false;
			}

			if (entity.Has<BulletStorageComponent>()) {
				auto bulletStorage = entity.Get<BulletStorageComponent>();
				if (inputService->IsKeyEventHappened(DIK_TAB, Key_press)) {
					bulletStorage->curGenreNum = (bulletStorage->curGenreNum + 1) % bulletStorage->MaxGenreNum;
					while (bulletStorage->genre[bulletStorage->curGenreNum] == 0) {
						bulletStorage->curGenreNum = (bulletStorage->curGenreNum + 1) % bulletStorage->MaxGenreNum;
					}
				}
				if (inputService->IsKeyEventHappened(DIK_J, Key_press)) {
					//射击
					behavior::Shoot(entity, *core, playerCom->direction);
					}
			}
			if (inputService->IsKeyEventHappened(DIK_1, Key_press)) {
				entity.Get<PropStorageComponent>()->useRequest = 0;
			}
			if (inputService->IsKeyEventHappened(DIK_2, Key_press)) {
				entity.Get<PropStorageComponent>()->useRequest = 1;
			}
			if (inputService->IsKeyEventHappened(DIK_3, Key_press)) {
				entity.Get<PropStorageComponent>()->useRequest = 2;
			}
		}
		else {
			if (entity.Has<TimingComponent>()) {
				auto StatusTime = entity.Get<TimingComponent>();
				if (StatusTime->InputDisabledTime < StatusTime->MaxInputDisabledTime) {
					StatusTime->InputDisabledTime += dt;
				}
				else {
					StatusTime->InputDisabledTime = 0;
					if (entity.Get<ObstacleComponent>()->yObstacle && entity.Get<ObstacleComponent>()->yDirection == Down) {
						entity.Get<VelocityComponent>()->vx = 0;
						entity.Get<VelocityComponent>()->vy = 0;
						entity.Activate<InputControlComponent>();
					}	
				}
				if (!entity.Has<HealthComponent>()) { //处于受伤保护的无敌状态
					if (StatusTime->TimeofInvincibleAfterHurt < StatusTime->MaxTimeofInvincibleAfterHurt) {
						StatusTime->TimeofInvincibleAfterHurt += dt;
					}
					else {
						StatusTime->TimeofInvincibleAfterHurt = 0;
						entity.Activate<HealthComponent>();
					}
				}
					
			}
		}
	});
}

std::string PlayerControlSystem::toString() {
	return std::string("player control system");
}

