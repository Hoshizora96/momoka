#pragma once

struct TileInfo {
	int width;
	int height;
	int friction;
};

inline TileInfo GetDefaultTileInfo() {
	TileInfo result;
	result.friction = 0;
	result.height = TILE_SIZE;
	result.width = TILE_SIZE;
	return result;
}