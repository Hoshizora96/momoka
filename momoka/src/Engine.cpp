#include "stdafx.h"
#include "Engine.h"
#include "util/ServiceLoader.h"
#include "services/InputService.h"
#include "services/GraphicService.h"
#include "util/JsonTools.h"
#include "util/Log.h"

#include <iostream>

// TODO: �������ȫ��������
#pragma warning(disable:4996)

LONGLONG Engine::m_freq = GetCurrentFrequency();
float Engine::m_refreshRate = 60.f;
ServiceLoader Engine::m_serviceLoader;

Engine::Engine() {
}

Engine::~Engine() {
	Shutdown();
}

bool Engine::Initialize() {
	auto pGraphicService = std::make_shared<GraphicService>();
	auto pInputService = std::make_shared<InputService>(pGraphicService->GetHwnd());

	m_serviceLoader.RegisterService(SERVICE_TYPE::Service_input, pInputService);
	m_serviceLoader.RegisterService(SERVICE_TYPE::Service_graphic, pGraphicService);
	LoadConfig();

	m_gameController_.Initialize();

	return true;
}

void Engine::Shutdown() {
	// TODO: ʵ����Դ���ͷ�
	if (m_debugConsole_)
		FreeConsole();
}


void Engine::Run() {
	bool gameover = false;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	m_gameController_.SwitchGameState(0);

	float dt = 0;

	auto inputService = m_serviceLoader.LocateService<InputService>(SERVICE_TYPE::Service_input);

	auto graphicService = m_serviceLoader.LocateService<GraphicService>(SERVICE_TYPE::Service_graphic);

	auto preTick = GetCurrentTick();

	while (!gameover) {
		// Windows Message Loop
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			gameover = true;
		}

		/************************************************************/
		/************************** Engine **************************/
		/************************************************************/

		auto curTick = GetCurrentTick();

		dt += (curTick - preTick) * 1000 / m_freq;
		preTick = curTick;

		while(dt >= 1000.f/ m_refreshRate) {
			inputService.lock()->RefreshBuffer();
			m_gameController_.Update();
			dt -= 1000.f / m_refreshRate;
		}
		graphicService.lock()->BeginDraw();
		m_gameController_.Render(dt);
		graphicService.lock()->EndDraw();
	}
}

void Engine::LoadConfig() {
	char* engineConfigFile = "content/config/engine.json";
	Document d;

	// �������false����ΪAllocConsole()ִ��ǰ�������׼�����д���ݣ�һд����̨�Ͳ�����ˡ�
	// ��Ҳ��֪����ν��������⣬����ܽ���Ͳ��ô���������ˡ�
	if(LoadJsonFile(d, engineConfigFile, false)) {
		int isConsole = d["log"]["console"].GetBool();
		if(isConsole) {
			m_debugConsole_ = true;
			AllocConsole();
			freopen("CONOUT$", "w+t", stdout);
		}

		std::string level = d["log"]["level"].GetString();
		momoka::Log::SetReportingLevel(level.c_str());
	}
}
