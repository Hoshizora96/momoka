#pragma once
#include "core/object/GameObjectPool.h"
#include "Engine.h"
#include "services/InputService.h"

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
}
