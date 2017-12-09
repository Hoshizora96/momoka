#pragma once

// �Ѱ�װ16�����
// ����ʱ�䣺2017/12/09 21:53:00

#include "core/object/EntityPool.h"
#include "core/object/components/BulletComponent.h"
#include "core/object/components/BulletStorageComponent.h"
#include "core/object/components/DamageBodyComponent.h"
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
#include "core/object/components/RenderComponent.h"
#include "core/object/components/TimingComponent.h"
#include "core/object/components/VelocityComponent.h"
#include "core/object/components/WeaponSlotComponent.h"

using GameEntityPool = EntityPool<
	// ���²����б�Ϊ��װ�����
	BulletComponent,
	BulletStorageComponent,
	DamageBodyComponent,
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
	RenderComponent,
	TimingComponent,
	VelocityComponent
>;