#include "stdafx.h"
#include "map/World.h"
#include "extlib/rapidjson/document.h"
#include "util/JsonTools.h"
#include "util/Log.h"

World::World(): m_pTileSet_(nullptr), m_pCollisionDetector_(nullptr), m_pHero_(nullptr), m_pCamera_(nullptr) {
	m_pTileSet_ = new TileSet();
	m_pCollisionDetector_ = new CollisionDetector(*m_pTileSet_);
	m_pHero_ = new Hero(*this);
	m_pCamera_ = new Camera();
}

void World::Render(Camera* camera) {
	m_pTileSet_->Render(m_pCamera_);
	m_pHero_->Render(m_pCamera_);
}

void World::Update(float dt) {
	m_pHero_->Update(dt);
	m_pCamera_->LookAt(m_pHero_->GetX(), m_pHero_->GetY());
}

CollisionDetector& World::GetCollisionDetector() const {
	return *m_pCollisionDetector_;
}

bool World::LoadConfig(char* path) {
	// TODO: 添加数据有效性判断

	MOMOKA_LOG(momoka::verbose) << "Load world config.";
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

Camera* World::GetCamera() const {
	return m_pCamera_;
}
