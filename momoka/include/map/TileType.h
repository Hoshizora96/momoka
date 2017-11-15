#pragma once
enum TILE_ATTRIBUTE {
	Attr_solid
};

class TileType {
private:
	int m_id_;
public:
	explicit TileType(int id)
		: m_id_(id) {
	}

	TileType();

	int GetId() const;
};