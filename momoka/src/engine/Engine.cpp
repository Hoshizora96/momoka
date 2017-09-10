#include "stdafx.h"
#include "engine/Engine.h"
#include "engine/DebugTools.h"


Engine* Engine::m_pUniEngineHandle_ = nullptr;

Engine::Engine(): m_applicationName_(nullptr),
                  m_hwnd_(nullptr),
                  m_pInputTools_(nullptr),
                  m_pGraphicsTools_(nullptr),
                  m_tickForDrawFrame_(0), m_tickForCountFrame_(0),
                  m_freq_(0), m_currentFps_(0),
                  m_frame_(0){
}

bool Engine::Initialize() {

	m_pUniEngineHandle_ = this;

	m_freq_ = GetCurrentFrequency();

	UINT screenWidth = 800, screenHeight = 600;

	// 此时m_hwnd_为NULL，不过不影响，传递的是引用
	m_pGraphicsTools_ = new GraphicsTools(m_hwnd_);
	if (!m_pGraphicsTools_) {
		return false;
	}

	if (!SUCCEEDED(m_pGraphicsTools_->Initialize())) {
		return false;
	}

	m_pDebugInfo_ = new DebugInfo();

	// 由于InitializeWindow中使用m_pGraphicsTools_获取dpi，所以先初始化m_pGraphicsTools_
	// dpi的获取是利用设备无关资源，所以即便在初始化m_pGraphicsTools_的时候m_hwnd_为NULL也可以正常运行
	if (!SUCCEEDED(InitializeWindow(screenWidth, screenHeight))) {
		return false;
	}

	m_pInputTools_ = new InputTools(m_hwnd_);
	if (!m_pInputTools_) {
		return false;
	}

	if (!SUCCEEDED(m_pInputTools_->Initialize())) {
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
	ZeroMemory(&msg, sizeof(MSG));

	bool gameover = false;
	while (!gameover) {

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			gameover = true;
		}
		else {
			const LONGLONG currentTick = GetCurrentTick();
			if (currentTick == 0) {
				gameover = true;
			}
			else if ((currentTick - m_tickForDrawFrame_) * 1000000 / m_freq_ > (1000000 / m_expectFps_)) {
				if (!Frame()) {
					gameover = true;
				}

				m_frame_++;
				if ((m_freq_ != 0) && (currentTick - m_tickForCountFrame_) * 1000 / m_freq_ > 1000 * 1) {
					m_currentFps_ = m_frame_;
					m_frame_ = 0;
					m_tickForCountFrame_ = currentTick;
				}
				m_tickForDrawFrame_ = currentTick;

				Update();
			}
		}
	}
}

int Engine::GetCurrentFps() const {
	return m_currentFps_;
}

int Engine::GetExpectFps() const {
	return m_expectFps_;
}

const Engine* Engine::GetUniEngineHandle() {
	return m_pUniEngineHandle_;
}

InputTools* Engine::GetInputTools() const {
	return m_pInputTools_;
}

GraphicsTools* Engine::GetGraphicsTools() const {
	return m_pGraphicsTools_;
}

LRESULT Engine::MessageHandler(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {

	switch (umsg) {
		// TODO: add message-handle action
	case WM_SIZE: {
		const UINT width = LOWORD(lParam);
		const UINT height = HIWORD(lParam);
		m_pGraphicsTools_->OnResize(width, height);
	}
		return 0;
	case WM_DISPLAYCHANGE: {
		InvalidateRect(m_hwnd_, nullptr, FALSE);
	}
		return 0;
	case WM_PAINT: {
		// TODO: 改成通用的渲染函数
		Frame();
		ValidateRect(m_hwnd_, nullptr);
	}
	default:
		return DefWindowProc(hwnd, umsg, wParam, lParam);
	}
}

bool Engine::Frame() {

	m_pGraphicsTools_->BeginDraw();
	// TODO: 这里添加帧的具体内容

	m_pGraphicsTools_->DrawDemo();
	m_pDebugInfo_->Draw();

	m_pGraphicsTools_->EndDraw();
	return true;
}

bool Engine::Update() {
	m_pInputTools_->Update();

	m_pDebugInfo_->Update();
	return true;
}

HRESULT Engine::InitializeWindow(UINT& windowWidth, UINT& windowHeight) {
	HRESULT hr;

	m_applicationName_ = L"Engine";

	WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
	wcex.lpszClassName = m_applicationName_;

	RegisterClassEx(&wcex);

	FLOAT dpiX, dpiY;
	m_pGraphicsTools_->GetDpi(dpiX, dpiY);

	windowWidth = static_cast<UINT>(ceil(windowWidth * dpiX / 96.f));
	windowHeight = static_cast<UINT>(ceil(windowHeight * dpiY / 96.f));

	m_hwnd_ = CreateWindow(
		m_applicationName_,
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
	m_pUniEngineHandle_ = nullptr;
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
		return m_pUniEngineHandle_->MessageHandler(hwnd, umsg, wParam, lParam);
	}
}
