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

	static LONGLONG m_freq;
	static float m_refreshRate;
	static ServiceLoader m_serviceLoader;

private:
	GameController m_gameController_;

	bool m_debugConsole_;

	void LoadConfig();
};