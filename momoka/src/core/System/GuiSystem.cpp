#include "stdafx.h"
#include "core/system/GuiSystem.h"
#include "Engine.h"
#include "services/GraphicService.h"
#include "core/GameCore.h"

void GuiSystem::Update(float& dt) {
	auto& players = core->groupManager.GetGroup<groups::PlayerGroup>();

	for (int i = 0; i < players.Size(); i++) {
		auto player = players[i];
		auto healthPower = player.Get<HealthComponent>();
		core->gui.DrawHeroHp(healthPower->healthPower, healthPower->maxHealthPower, 5, 5);
	}
	
}

std::string GuiSystem::toString() {
	return std::string("gui system");
}
