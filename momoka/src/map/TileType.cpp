#include "stdafx.h"
#include "map/TileType.h"

TileType::TileType() {
	m_id_ = 0;
}

int TileType::GetId() const {
	return m_id_;
}
