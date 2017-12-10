#pragma once
#include "core/object/components/Component.h"

#define left 1
#define right 0
class PlayerComponent:public Component {
public:
	bool direction = right;
};