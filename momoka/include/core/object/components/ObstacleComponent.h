#pragma once
#include "core/object/components/Component.h"
#include "util/Direction.h"

class ObstacleComponent: public Component {
public:
	float obstacleWidth = 0;
	float obstacleHeight = 0;

	bool xObstacle = false;
	bool yObstacle = false;

	DIRECTION xDirection;
	DIRECTION yDirection;
};