#pragma once

struct TileInfo {
	int width;
	int height;
	int friction;
};

inline TileInfo GetDefaultTileInfo() {
	TileInfo result;
	result.friction = 0;
	result.height = momoka_global::TILE_SIZE;
	result.width = momoka_global::TILE_SIZE;
	return result;
}