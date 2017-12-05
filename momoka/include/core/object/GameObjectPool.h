#pragma once
#include "core/object/EntityPool.h"
#include "core/object/components/ObstacleComponent.h"
#include "core/object/components/GravityComponent.h"
#include "core/object/components/VelocityComponent.h"
#include "core/object/components/MoveComponent.h"
#include "core/object/components/JumpComponent.h"
#include "core/object/components/PositionComponent.h"
#include "core/object/components/RenderComponent.h"
#include "core/object/components/PlayerComponent.h"

using GameEntityPool = EntityPool<
	// ���²����б�Ϊ��װ�����
	ObstacleComponent,
	GravityComponent,
	VelocityComponent,
	MoveComponent,
	JumpComponent,
	PositionComponent,
	RenderComponent,
	PlayerComponent
>;