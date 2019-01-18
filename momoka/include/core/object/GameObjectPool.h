#pragma once

// 已安装21个组件
// 更新时间：2018/01/07 22:30:27

#include "core/object/EntityPool.h"
#include "core/object/components/AnimationComponent.h"
#include "core/object/components/BulletComponent.h"
#include "core/object/components/BulletStorageComponent.h"
#include "core/object/components/DamageBodyComponent.h"
#include "core/object/components/DeadComponent.h"
#include "core/object/components/DetectAreaComponent.h"
#include "core/object/components/FriendComponent.h"
#include "core/object/components/GravityComponent.h"
#include "core/object/components/HealthComponent.h"
#include "core/object/components/InputControlComponent.h"
#include "core/object/components/JumpComponent.h"
#include "core/object/components/MonsterComponent.h"
#include "core/object/components/MoveComponent.h"
#include "core/object/components/ObstacleComponent.h"
#include "core/object/components/PlayerComponent.h"
#include "core/object/components/PositionComponent.h"
#include "core/object/components/PropComponent.h"
#include "core/object/components/PropStorageComponent.h"
#include "core/object/components/RenderComponent.h"
#include "core/object/components/TimingComponent.h"
#include "core/object/components/VelocityComponent.h"
#include "core/object/components/WeaponSlotComponent.h"

using GameEntityPool = EntityPool<
	// 以下参数列表为安装的组件
	AnimationComponent,
	BulletComponent,
	BulletStorageComponent,
	DamageBodyComponent,
	DeadComponent,
	DetectAreaComponent,
	FriendComponent,
	GravityComponent,
	HealthComponent,
	InputControlComponent,
	JumpComponent,
	MonsterComponent,
	MoveComponent,
	ObstacleComponent,
	PlayerComponent,
	PositionComponent,
	PropComponent,
	PropStorageComponent,
	RenderComponent,
	TimingComponent,
	VelocityComponent
>;