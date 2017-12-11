#include "stdafx.h"
#include "core/system/PlayerControlSystem.h"
#include "core/factory/BulletFactory.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/InputService.h"
#include "util/Log.h"
#include "core/utility/bahavior.h"

void PlayerControlSystem::Update(float& dt, GameCore& core) {
	auto inputService = Engine::serviceLoader.LocateService<InputService>(Service_input).lock();
	core.entityPool.Each<
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
				playerCom->direction = Right;
			}
			else if (inputService->IsKeyEventHappened(DIK_A)) {
				behavior::Running(entity, dt, Left);
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



			if (entity.Has<BulletStorageComponent>()) {
				auto bulletStorage = entity.Get<BulletStorageComponent>();
				if (inputService->IsKeyEventHappened(DIK_TAB, Key_press)) {
					bulletStorage->curGenreNum = (bulletStorage->curGenreNum + 1) % bulletStorage->MaxGenreNum;
					while (bulletStorage->genre[bulletStorage->curGenreNum] == 0) {
						bulletStorage->curGenreNum = (bulletStorage->curGenreNum + 1) % bulletStorage->MaxGenreNum;
					}
				}
				if (inputService->IsKeyEventHappened(DIK_J, Key_press)) {
					//Éä»÷
					BulletFactory bulletFactory;
					auto bullet = bulletFactory.Create(core.entityPool, bulletStorage->curGenreNum);
					if (playerCom->direction == Right) {
						bullet.Get<PositionComponent>()->x = entity.Get<PositionComponent>()->x + momoka::TILE_SIZE;
						bullet.Get<PositionComponent>()->y = entity.Get<PositionComponent>()->y + momoka::TILE_SIZE;
					}
					else {
						bullet.Get<PositionComponent>()->x = entity.Get<PositionComponent>()->x;
						bullet.Get<PositionComponent>()->y = entity.Get<PositionComponent>()->y + momoka::TILE_SIZE;
						bullet.Get<VelocityComponent>()->vx = -bullet.Get<VelocityComponent>()->vx;
					}
				}
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
						entity.Activate<InputControlComponent>();
					}
				}
			}
		}
	});
}

