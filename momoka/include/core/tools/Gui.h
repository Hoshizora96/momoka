#pragma once
#include <string>

class Gui {
	ID2D1Bitmap* heroHPBar;
	ID2D1Bitmap* enemyHPBar;
public:
	void DrawDebugText(std::string text);
	void DrawHeroHp(float currentValue, float maxValue, int posX, int posY);
	void DrawEnemyHp(float currentValue, float maxValue, int posX, int posY);

	Gui();
};
