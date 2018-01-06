#pragma once
#include "core/object/GameObjectPool.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "core/factory/BulletFactory.h"

namespace behavior {
	/**
	 * \brief 使entity水平方向移动
	 * \param entity 目标entity
	 * \param dt 时间增量
	 * \param direction 移动方向，注意只能为Left或Right
	 */
	inline void Running(GameEntityPool::Entity& entity, float& dt, DIRECTION direction) {
		auto velocityCom = entity.Get<VelocityComponent>();
		if (entity.Has<VelocityComponent, MoveComponent>()) {
			switch (direction) {
			case Left:
				velocityCom->vx = -entity.Get<MoveComponent>()->runningVelocity;
				break;
			case Right:
				velocityCom->vx = entity.Get<MoveComponent>()->runningVelocity;
				break;
			default:
				break;
			}
		}
	}

	/**
	 * \brief 使entity处于 vx==0 的状态
	 * \param entity 目标entity
	 */
	inline void Stand(GameEntityPool::Entity& entity) {
		auto velocityCom = entity.Get<VelocityComponent>();
		velocityCom->vx = 0;
	}

	/**
	 * \brief 使目标entity跳跃
	 * \param entity 目标entity
	 * \param dt 时间增量
	 */
	inline void Jump(GameEntityPool::Entity& entity, float& dt) {
		//		auto inputService = Engine::serviceLoader.LocateService<InputService>(Service_input).lock();
		auto velocityCom = entity.Get<VelocityComponent>();
		if (entity.Has<ObstacleComponent, JumpComponent>()) {
			auto jumpCom = entity.Get<JumpComponent>();
			auto obstacleCom = entity.Get<ObstacleComponent>();
			if (obstacleCom->yObstacle && obstacleCom->yDirection == Down) {
				jumpCom->jumpedTimes = 0;
			}
			if (jumpCom->jumpedTimes < jumpCom->maxJumpTimes
				&& jumpCom->floatTime < jumpCom->maxFloatTime) {
				velocityCom->vy = -jumpCom->jumpVelocity;
				jumpCom->floatTime += dt;
			}
		}
	}

	/**
	 * \brief 使Entity停止跳跃动作
	 * \param entity 目标entity
	 */
	inline void StopJumpAndFall(GameEntityPool::Entity& entity) {
		auto velocityCom = entity.Get<VelocityComponent>();
		if (entity.Has<ObstacleComponent, JumpComponent>()) {
			auto jumpCom = entity.Get<JumpComponent>();
			if (jumpCom->floatTime < jumpCom->maxFloatTime)
				velocityCom->vy = 0;
			jumpCom->jumpedTimes++;
			jumpCom->floatTime = 0;
		}
	}

	/**
	 * \brief 使entity产生一个击退的效果
	 * \param entity 目标entity
	 * \param direction 击退方向，只能是Left或Right
	 */
	inline void Repel(GameEntityPool::Entity& entity, DIRECTION direction) {
		auto velocityCom = entity.Get<VelocityComponent>();
		if(direction==Left) {
			velocityCom->vx = -500;
			velocityCom->vy = -1000;
		}
		else if(direction==Right) {
			velocityCom->vx = 500;
			velocityCom->vy = -1000;
		}
	}

	inline void Shoot(GameEntityPool::Entity& entity, GameCore& core, DIRECTION direction) {
		auto bulletStorage = entity.Get<BulletStorageComponent>();
		BulletFactory bulletFactory;
		GameEntityPool::Entity bullet = bulletFactory.Create(core.entityPool, bulletStorage->curGenreNum);
		if (entity.Has<PlayerComponent>()) {
			bullet.Activate<FriendComponent>();
		}
		if (direction == Right) {
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
