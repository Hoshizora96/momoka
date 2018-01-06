#include "stdafx.h"
#include "core/tools/Gui.h"
#include "Engine.h"
#include "services/GraphicService.h"


void Gui::DrawDebugText(std::string text) {
}

void Gui::DrawHeroHp(int currentValue, int maxValue, int posX, int posY) {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	graphicService->DrawBitmap(heroHPBar);
}

void Gui::DrawEnemyHp(int currentValue, int maxValue, int posX, int posY) {
}

Gui::Gui() {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	graphicService->LoadBitMap(L"content/assert/hero-hp-bar.PNG", &heroHPBar);
}
