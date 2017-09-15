#pragma once

struct TileInfo {
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

private:
	int m_type_;
	int m_posX_;
	int m_posY_;
};