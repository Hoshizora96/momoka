#pragma once
#include "core/object/GameObjectPool.h"
#include "Engine.h"
#include "services/InputService.h"

namespace behavior {
	/**
	 * \brief ʹentityˮƽ�����ƶ�
	 * \param entity Ŀ��entity
	 * \param dt ʱ������
	 * \param direction �ƶ�����ע��ֻ��ΪLeft��Right
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
	 * \brief ʹentity���� vx==0 ��״̬
	 * \param entity Ŀ��entity
	 */
	inline void Stand(GameEntityPool::Entity& entity) {
		auto velocityCom = entity.Get<VelocityComponent>();
		velocityCom->vx = 0;
	}

	/**
	 * \brief ʹĿ��entity��Ծ
	 * \param entity Ŀ��entity
	 * \param dt ʱ������
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
	 * \brief ʹEntityֹͣ��Ծ����
	 * \param entity Ŀ��entity
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
	 * \brief ʹentity����һ�����˵�Ч��
	 * \param entity Ŀ��entity
	 * \param direction ���˷���ֻ����Left��Right
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
}
