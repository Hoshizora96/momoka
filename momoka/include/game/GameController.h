#pragma once
#include "util/ServiceLoader.h"
#include "objects/Entity.h"
#include <map>

class GameController {
public:
	GameController(ServiceLoader serviceLoader);
	~GameController();
	
};