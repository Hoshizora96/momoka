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
	// 以下参数列表为安装的组件
	ObstacleComponent,
	GravityComponent,
	VelocityComponent,
	MoveComponent,
	JumpComponent,
	PositionComponent,
	RenderComponent,
	PlayerComponent
>;