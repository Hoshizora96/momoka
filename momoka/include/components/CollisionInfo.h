#pragma once
#include "components/Direction.h"
#include "map/TileType.h"

class CollisionInfo {
public:
	bool isOnGround;

	bool isCollisionX;
	bool isCollisionY;

	Direction directionX;
	Direction directionY;
	
	int tileType;

	// ������ע��ĿǰtileX��tileY��ʱû��ʹ�ã�Ҳ����˵��ײ������������ֵ����仯������
	int tileX;
	int tileY;
	
	int correctedX;
	int correctedY;

	float correctedVelocityX;
	float correctedVelocityY;

	CollisionInfo();

	void ClearAllFlag();
	void SetCollision(Direction dir, float corrected);
};