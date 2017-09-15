#pragma once

class TileInfo {
public:
	TileInfo(int width, int height, int friction)
		: m_width(width),
		  m_height(height),
		  m_friction(friction) {
	}

	int m_width;
	int m_height;
	int m_friction;
};

class Tile {
public:
	Tile(int type, int posX, int posY)
		: m_type_(type),
		  m_posX_(posX),
		  m_posY_(posY) {
	}

	int m_type_;
	int m_posX_;
	int m_posY_;
};