#pragma once
#include "stdafx.h"
#include "util/ServiceLoader.h"
#include "game/GameController.h"

class Engine {
public:
	Engine();
	~Engine();

	bool Initialize();
	void Shutdown();
	void Run();

	static LONGLONG freq;
	static float refreshRate;
	static ServiceLoader serviceLoader;
	static bool aSecond;

private:
	GameController m_gameController_;

	bool m_debugConsole_;

	bool LoadConfig();
};