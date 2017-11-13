#pragma once
#include "map/TileType.h"
#include "util/HashedString.h"
#include <map>

typedef __int64 TileMapKey;
typedef std::map<TileMapKey, int> TileMap;
typedef std::map<int, TileType> TileTypeMap;

class TileSet {
public:
	TileSet();
	void AddTile(int x, int y, int type);
	void AddTileType(TileType type);
	void DeleteTile(int x, int y);
	bool IsTileExist(int x, int y);
	TileType& GetTileType(int x, int y);
	TileType& GetTileType(int id);
	int GetTileTypeId(int x, int y);

	bool LoadTileType();
	void Render(float dt);
private:
	TileTypeMap m_typeMap_;
	TileMap m_tileMap_;
	static TileMapKey TileMapKeyConvert(long long xTile, long long yTile);
};
