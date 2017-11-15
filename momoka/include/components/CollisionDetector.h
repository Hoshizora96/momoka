#pragma once
#include "components/CollisionInfo.h"
#include "map/TileSet.h"
#include "components/PhysicalBody.h"
#include "HitBox.h"

class CollisionDetector {
public:
	explicit CollisionDetector(TileSet& tileSet);
	
	// ���body��tile�Ĺ�����ײ������ζ�Żᷢ���赲
	CollisionInfo CheckTileCollision(PhysicalBody &body) const;
	bool CheckHitBoxCollison(HitBox myHitBox, HitBox opponentHitBox);
	// bool CheckCollision();
private:
	// �������ĳһ����ֵ�Ƿ�λ��Tile�߽���
	static bool IsOnTileLine(float o);
	TileSet& m_tileSet;
};
