#include "stdafx.h"
#include "core/map/TilePool.h"
#include "extlib/rapidjson/document.h"
#include "util/JsonTools.h"
#include "Engine.h"


bool TilePool::HasTile(int tileX, int tileY) {
	return m_tileMap_.find(TileHashConvert(tileX, tileY)) != m_tileMap_.end();
}

TilePool::Type* TilePool::GetType(int tileX, int tileY) {
	/*
	 * �Ҹ��˸о������ʵ�ֺܱ�����Ȼ��û�б���뷨
	 * �����Ͼ�����Ĳ�ѯ�������Ǿ���Ҫ���ģ�����̫������
	 * �ҵĿ���������Ժ��ѯ����Ļ��������洦��
	 */

	// һ�β��
	auto item = m_tileMap_.find(TileHashConvert(tileX, tileY));
	if (item != m_tileMap_.end()) {
		// ���β��
		auto type = m_typeMap_.find(item->second);
		if (type != m_typeMap_.end()) {
			return &(type->second);
		}
		else {
			// TODO: ���������Ӳ����
		}
	}
	return nullptr;

}

size_t TilePool::Count() const {
	return m_tileMap_.size();
}

bool TilePool::LoadConfig(char* path) {
	rapidjson::Document d;
	// "content/tiles/tile-type-test.json"
	if (LoadJsonFile(d, path)) {
		auto allType = d["types"].GetArray();
		for (auto& type : allType) {
			Type t(type["id"].GetInt());
			AddTileType(t);
		}
		return true;
	}
	return false;
}

void TilePool::AddTile(int tileX, int tileY, TypeIndex typeIndex) {
	m_tileMap_[TileHashConvert(tileX, tileY)] = typeIndex;
}

void TilePool::Render(Camera& camera) {
	for (const auto tile : m_tileMap_) {
		int x = tile.first >> 20;
		int y = tile.first - (x << 20);
		auto type = m_typeMap_[tile.second];
		camera.DrawRect(x * momoka::TILE_SIZE, y * momoka::TILE_SIZE, momoka::TILE_SIZE,
			momoka::TILE_SIZE);
	}
}

void TilePool::AddTileType(Type& type) {
	m_typeMap_[type.GetId()] = type;
}

inline TilePool::TileHash TilePool::TileHashConvert(int tileX, int tileY) {
	return (tileX << 20) + tileY;
}
