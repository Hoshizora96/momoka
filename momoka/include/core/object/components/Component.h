#pragma once
#include "util/HashedString.h"

class Component {
public:
	virtual ~Component() = default;
};

class SingletonComponent {
};