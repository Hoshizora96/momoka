#pragma once
#include "stdafx.h"
#include "core/tools/animator/Animator.h"
#include "core/object/components/Component.h"

class AnimationComponent:public Component {
public:
	Animator::AnimationType animationType = Animator::Stand;
	float animationPlayedTime = 0;
};