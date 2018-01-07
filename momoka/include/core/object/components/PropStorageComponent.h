#pragma once
#include "core/object/components/Component.h"
#define SpecialPropNum 3

class PropStorageComponent :public Component {
public:
	int PropStorage[SpecialPropNum] = { 0, 0, 0};
	int useRequest = -1;
};