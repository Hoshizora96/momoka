#include "stdafx.h"
#include "engine/Engine.h"

Engine* Engine::m_pApplicationHandle_ = nullptr;

Engine::Engine(): m_applicationName_(nullptr),
                  m_hwnd_(nullptr),
                  m_pInputTools_(nullptr),
                  m_pGraphicsTools_(nullptr) {
}

bool Engine::Initialize() {

	UINT screenWidth = 800, screenHeight = 600;

	m_pGraphicsTools_ = new GraphicsTools(m_hwnd_);
	if (!m_pGraphicsTools_) {
		return false;
	}

	if (!SUCCEEDED(m_pGraphicsTools_->Initialize())) {
		return false;
	}

	if (!SUCCEEDED(InitializeWindow(screenWidth, screenHeight))) {
		return false;
	}

	if (!m_pInputTools_->Initialize()) {
		return false;
	}

	m_pInputTools_ = new InputTools();
	if (!m_pInputTools_) {
		return false;
	}

	return true;

}

void Engine::Shutdown() {
	if (m_pGraphicsTools_) {
		m_pGraphicsTools_->Shutdown();
		delete m_pGraphicsTools_;
		m_pGraphicsTools_ = nullptr;
	}

	if (m_pInputTools_) {
		m_pInputTools_->Shutdown();
		delete m_pInputTools_;
		m_pInputTools_ = nullptr;
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

LRESULT Engine::MessageHandler(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) const {
	switch (umsg) {
		// TODO: add message-handle action
	case WM_SIZE: {
		const UINT width = LOWORD(lParam);
		const UINT height = HIWORD(lParam);
		m_pGraphicsTools_->OnResize(width, height);
	}
		return 0;
	case WM_DISPLAYCHANGE:
		{
			InvalidateRect(m_hwnd_, nullptr, FALSE);
		}
		return 0;
	case WM_PAINT:
		{
		// TODO: 改成通用的渲染函数
			m_pGraphicsTools_->DrawRect();
			ValidateRect(m_hwnd_, nullptr);
		}
	default:
		return DefWindowProc(hwnd, umsg, wParam, lParam);
	}
}

bool Engine::Frame() {
	bool result;
	// TODO: add some action
	m_pGraphicsTools_->DrawRect();
	return true;
}

HRESULT Engine::InitializeWindow(UINT& windowWidth, UINT& windowHeight) {
	HRESULT hr;

	m_pApplicationHandle_ = this;

	m_applicationName_ = L"Engine";

	WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
	wcex.lpszClassName = L"D2DDemoApp";

	RegisterClassEx(&wcex);

	FLOAT dpiX, dpiY;
	m_pGraphicsTools_->GetDpi(dpiX, dpiY);

	windowWidth = static_cast<UINT>(ceil(windowWidth * dpiX / 96.f));
	windowHeight = static_cast<UINT>(ceil(windowHeight * dpiY / 96.f));
	m_hwnd_ = CreateWindow(
		L"D2DDemoApp",
		L"Direct2D Demo App",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // posX
		CW_USEDEFAULT, // posY
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	hr = m_hwnd_ ? S_OK : E_FAIL;
	if (SUCCEEDED(hr)) {
		ShowWindow(m_hwnd_, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd_);
		SetFocus(m_hwnd_);
		ShowCursor(true);
	}

	return hr;
}

void Engine::ShutdownWindow() {
	ShowCursor(true);

	DestroyWindow(m_hwnd_);
	m_hwnd_ = nullptr;

	UnregisterClass(m_applicationName_, HINST_THISCOMPONENT);

	// Release the pointer to this class.
	m_pApplicationHandle_ = nullptr;
}

LRESULT Engine::WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {
	// 这个函数只处理一些通用消息
	// 具体涉及绘图与输入操作的消息由m_pApplicationHandle_转入Engine内部处理
	// 没办法WndProc必须是静态函数，大概吧
	switch (umsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return m_pApplicationHandle_->MessageHandler(hwnd, umsg, wParam, lParam);
	}
}
