#include "stdafx.h"
#include "map/World.h"
#include "extlib/rapidjson/document.h"
#include "util/JsonTools.h"

World::World(): m_pTileSet_(nullptr), m_pCollisionDetector_(nullptr), m_pHero_(nullptr) {
	m_pTileSet_ = new TileSet();
	m_pCollisionDetector_ = new CollisionDetector(*m_pTileSet_);
	m_pHero_ = new Hero(*this);
}

void World::Render(float dt) {
	m_pTileSet_->Render(dt);
	m_pHero_->Render(dt);
}

void World::Update(float dt) {
	m_pHero_->Update(dt);
}

CollisionDetector& World::GetCollisionDetector() const {
	return *m_pCollisionDetector_;
}

bool World::LoadConfig(char* path) {
	// TODO: 添加数据有效性判断
	rapidjson::Document d;
	m_pTileSet_->LoadTileType("content/tiles/tile-type-test.json");
	m_pHero_->LoadConfig("content/objects/hero.json");

	if (LoadJsonFile(d, "content/stages/map-test1.json")) {
		auto tileArray = d["room"][0]["tile"].GetArray();
		for (auto& tile : tileArray) {
			m_pTileSet_->AddTile(tile[0].GetInt(), tile[1].GetInt(), tile[2].GetInt());
		}
		return true;
	}
	return true;
}
