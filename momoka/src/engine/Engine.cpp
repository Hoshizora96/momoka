#include "stdafx.h"
#include "engine/Engine.h"

Engine* Engine::ApplicationHandle = nullptr;

Engine::Engine() {
}

bool Engine::Initialize() {

	UINT screenWidth = 800, screenHeight = 600;

	m_pGraphicsTools = new GraphicsTools();
	if (!m_pGraphicsTools) {
		return false;
	}

	if (!SUCCEEDED(m_pGraphicsTools->Initialize(m_hwnd))){
		return false;
	}

	if (!SUCCEEDED(InitializeWindow(screenWidth, screenHeight))) {
		return false;
	}

	if (!m_pInputTools->Initialize()) {
		return false;
	}

	m_pInputTools = new InputTools();
	if (!m_pInputTools) {
		return false;
	}

	return true;

}

void Engine::Shutdown() {
	if (m_pGraphicsTools) {
		m_pGraphicsTools->Shutdown();
		delete m_pGraphicsTools;
		m_pGraphicsTools = nullptr;
	}

	if (m_pInputTools) {
		m_pInputTools->Shutdown();
		delete m_pInputTools;
		m_pInputTools = nullptr;
	}

	ShutdownWindow();
}

void Engine::Run() {
	MSG msg;
	bool done;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			if (!Frame()) {
				done = true;
			}
		}
	}
}

LRESULT Engine::MessageHandler(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {
	switch (umsg) {
		// TODO: add message-handle action
	default:
		return DefWindowProc(hwnd, umsg, wParam, lParam);
	}
	return LRESULT();
}

bool Engine::Frame() {
	bool result;
	// TODO: add some action
	return true;
}

HRESULT Engine::InitializeWindow(UINT& windowWidth, UINT& windowHeight) {
	HRESULT hr;

	ApplicationHandle = this;

	m_applicationName = L"Engine";

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Engine::WndProc;
	wcex.cbClsExtra = 0;
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"D2DDemoApp";

	RegisterClassEx(&wcex);

	FLOAT dpiX, dpiY;
	m_pGraphicsTools->GetDpi(dpiX, dpiY);

	windowWidth = static_cast<UINT>(ceil(windowWidth * dpiX / 96.f));
	windowHeight = static_cast<UINT>(ceil(windowHeight * dpiY / 96.f));
	m_hwnd = CreateWindow(
		L"D2DDemoApp",
		L"Direct2D Demo App",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,  // posX
		CW_USEDEFAULT,  // posY
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	hr = m_hwnd ? S_OK : E_FAIL;
	if (SUCCEEDED(hr)) {
		ShowWindow(m_hwnd, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd);
		SetFocus(m_hwnd);
		ShowCursor(true);
	}

	return hr;
}

void Engine::ShutdownWindow() {
	ShowCursor(true);

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, HINST_THISCOMPONENT);

	// Release the pointer to this class.
	ApplicationHandle = nullptr;
}

LRESULT Engine::WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {
	switch (umsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:		
		PostQuitMessage(0);
		return 0;
	default:
		return ApplicationHandle->MessageHandler(hwnd, umsg, wParam, lParam);
	}
	return LRESULT();
}
