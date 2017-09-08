#include "stdafx.h"
#include "engine/Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	Engine* pEngine;
	bool result;

	// 创建Engine对象。
	pEngine = new Engine();
	if (!pEngine) {
		return 0;
	}

	//初始化并运行Engine对象。
	result = pEngine->Initialize();
	if (result) {
		pEngine->Run();
	}

	// 关闭并释放Engine对象。
	pEngine->Shutdown();

	delete pEngine;
	pEngine = nullptr;
	return 0;
}
