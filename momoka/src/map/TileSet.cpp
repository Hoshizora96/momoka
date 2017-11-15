#include "stdafx.h"
#include "map/TileSet.h"
#include "util/JsonTools.h"
#include "services/GraphicService.h"
#include "Engine.h"

TileSet::TileSet() {
}

void TileSet::AddTile(int x, int y, int type) {
	m_tileMap_[TileMapKeyConvert(x, y)] = type;
}

void TileSet::AddTileType(TileType type) {
	m_typeMap_[type.GetId()] = type;
}

void TileSet::DeleteTile(int x, int y) {
	// TODO: 添加移除元素的部分
}

bool TileSet::IsTileExist(int x, int y) {
	auto tile = m_tileMap_.find(TileMapKeyConvert(x, y));
	if (tile != m_tileMap_.end()) {
		return true;
	}
	return false;
}

TileType& TileSet::GetTileType(int x, int y) {
	auto tile = m_tileMap_.find(TileMapKeyConvert(x, y));
	if (tile != m_tileMap_.end()) {
		auto type = m_typeMap_.find(tile->second);
		if (type != m_typeMap_.end()) {
			return type->second;
		}
	}
	// TODO: 做一个异常类，处理不存在默认tile类型的情况
	auto defaultType = m_typeMap_[0];
	return defaultType;
}

bool TileSet::LoadTileType(char* path) {
	rapidjson::Document d;
	// "content/tiles/tile-type-test.json"
	if (LoadJsonFile(d, path)) {
		auto allType = d["types"].GetArray();
		for (auto& type : allType) {
			TileType t(type["id"].GetInt());
			m_typeMap_[t.GetId()] = t;
		}
		return true;
	}
	return false;
}

void TileSet::Render(float dt) {
	auto pGraphicService = Engine::m_serviceLoader.LocateService<GraphicService>(
		SERVICE_TYPE::Service_graphic).lock();
	for (const auto tile : m_tileMap_) {
		int y = tile.first % 1000000;
		int x = (tile.first - y) / 1000000;
		auto type = m_typeMap_[tile.second];
		pGraphicService->DrawRect(x * momoka_global::TILE_SIZE, y * momoka_global::TILE_SIZE, momoka_global::TILE_SIZE,
		                          momoka_global::TILE_SIZE);
	}
}

TileMapKey TileSet::TileMapKeyConvert(long long xTile, long long yTile) {
	return xTile * 1000000 + yTile;
}

TileSet::~TileSet() {
}

TileType& TileSet::GetTileType(int id) {
	auto type = m_typeMap_.find(id);
	if (type != m_typeMap_.end()) {
		return type->second;
	}
	// TODO: 做一个异常类，处理不存在默认tile类型的情况
	auto defaultType = m_typeMap_[0];
	return defaultType;
}

int TileSet::GetTileTypeId(int x, int y) {
	auto tile = m_tileMap_.find(TileMapKeyConvert(x, y));
	if (tile != m_tileMap_.end()) {
		return tile->second;
	}
	return 0;
}
