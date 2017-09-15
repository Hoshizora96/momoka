#include "stdafx.h"
#include "Engine.h"
#include "util/ServiceLoader.h"
#include "services/InputService.h"
#include "services/GraphicService.h"
#include "services/WindowService.h"

LONGLONG Engine::m_freq = GetCurrentFrequency();
float Engine::m_refreshRate = 60.f;
ServiceLoader Engine::m_serviceLoader;

Engine::Engine() {

}

Engine::~Engine() {
}

bool Engine::Initialize() {

	auto pWindowService = std::make_shared<WindowService>(L"momoka");
	auto pGraphicService = std::make_shared<GraphicService>(pWindowService->GetHwnd());
	auto pInputService = std::make_shared<InputService>(pWindowService->GetHwnd());

	m_serviceLoader.RegisterService(SERVICE_TYPE::windowService, pWindowService);
	m_serviceLoader.RegisterService(SERVICE_TYPE::inputService, pInputService);
	m_serviceLoader.RegisterService(SERVICE_TYPE::graphicService, pGraphicService);


	return true;
}

void Engine::Shutdown() {

}

void Engine::Run() {
	auto preTick = GetCurrentTick();
	bool gameover = false;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));


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

		auto inputService = m_serviceLoader.LocateService<InputService>(SERVICE_TYPE::inputService);
		inputService.lock()->RefreshBuffer();

		auto curTick = GetCurrentTick();
		if((curTick - preTick)*1000/m_freq > 1.f/60.f * 1000) {
			
		}
	}

}
