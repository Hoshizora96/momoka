#include "stdafx.h"
#include "core/system/GuiSystem.h"
#include "Engine.h"
#include "services/GraphicService.h"
#include "core/GameCore.h"

void GuiSystem::Update(float& dt) {
	auto& players = core->groupManager.GetGroup<groups::PlayerGroup>();
	auto& monsters = core->groupManager.GetGroup<groups::MonsterGroup>();

	for (int i = 0; i < players.Size(); i++) {
		auto player = players[i];
		auto healthPower = player.Get<HealthComponent>();
		core->gui.DrawHeroHp(healthPower->healthPower, healthPower->maxHealthPower, 5, 5);
	}


	for (int i = 0; i < monsters.Size(); i++) {
		auto monster = monsters[i];
		auto healthPower = monster.Get<HealthComponent>();
		auto position = monster.Get<PositionComponent>();
		auto newPosition = core->camera.TransformedCoordinate(position->x + 5, position->y - 15);
		core->gui.DrawEnemyHp(healthPower->healthPower, healthPower->maxHealthPower, newPosition.GetX(), newPosition.GetY());
	}



	
}

std::string GuiSystem::toString() {
	return std::string("gui system");
}
