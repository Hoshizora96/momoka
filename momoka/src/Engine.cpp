#include "stdafx.h"
#include "Engine.h"
#include "util/ServiceLoader.h"
#include "services/InputService.h"
#include "services/GraphicService.h"

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
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);

	auto pGraphicService = std::make_shared<GraphicService>();
	auto pInputService = std::make_shared<InputService>(pGraphicService->GetHwnd());

	m_serviceLoader.RegisterService(SERVICE_TYPE::Service_input, pInputService);
	m_serviceLoader.RegisterService(SERVICE_TYPE::Service_graphic, pGraphicService);

	m_gameController_.Initialize();

	return true;
}

void Engine::Shutdown() {
	// TODO: 实现资源的释放
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
