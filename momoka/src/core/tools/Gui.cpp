#include "stdafx.h"
#include "core/tools/Gui.h"
#include "Engine.h"
#include "services/GraphicService.h"


void Gui::DrawDebugText(std::string text) {
}

void Gui::DrawHeroHp(float currentValue, float maxValue, int posX, int posY) {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	auto hp = currentValue / maxValue;
	graphicService->DrawBitmap(heroHPBar, posX, posY);
	graphicService->DrawRect(posX+79, posY+12, (273 - 79)*hp, 50 - 12,  GraphicService::Red);
}

void Gui::DrawEnemyHp(int currentValue, int maxValue, int posX, int posY) {
}

Gui::Gui() {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	graphicService->LoadBitMap(L"content/assert/hero-hp-bar.PNG", &heroHPBar);
}
