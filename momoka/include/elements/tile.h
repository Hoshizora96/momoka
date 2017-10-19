#pragma once

#include "global.h"
#include <map>
#include <vector>

struct TileType {
	int width;
	int height;
	int friction;
};

typedef __int64 TileMapKey;
typedef std::map<short, TileType> TileTpyeMap;
typedef std::map<TileMapKey, short> TileMap;
typedef std::vector<TileMapKey> TileKeyVector;

inline TileMapKey TileMapKeyConvert(long long xTile, long long yTile) {
	return xTile * momoka_global::MULX + yTile;
}

inline TileType GetDefaultTileInfo() {
	TileType result;
	result.friction = 0;
	result.height = momoka_global::TILE_SIZE;
	result.width = momoka_global::TILE_SIZE;
	return result;
}
