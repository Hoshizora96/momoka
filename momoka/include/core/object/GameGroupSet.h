#pragma once
#include "GameObjectPool.h"
#include "GroupManager.h"
#define GROUP GameEntityPool::Group

namespace groups {
	using PlayerGroup = GROUP<HealthComponent, VelocityComponent, PositionComponent, PlayerComponent>;
	using MonsterGroup = GROUP<HealthComponent, VelocityComponent, PositionComponent, MonsterComponent>;
	using FriendBulletGroup = GROUP<HealthComponent, VelocityComponent, PositionComponent, FriendComponent, BulletComponent>;
	using ObstacleGroup = GROUP<ObstacleComponent, VelocityComponent, PositionComponent>;
	using AnimatorGroup = GROUP<AnimationComponent>;
}

using GameGroupSet = GroupManager<
	groups::PlayerGroup,
	groups::FriendBulletGroup,
	groups::MonsterGroup,
	groups::ObstacleGroup,
	groups::AnimatorGroup
>;
