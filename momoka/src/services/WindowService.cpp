#include "stdafx.h"
#include "services/WindowService.h"

WindowService::WindowService(LPCWSTR appName) {
	m_appName_ = appName;
	m_windowWidth_ = 640;
	m_windowHeight_ = 480;

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
	wcex.lpszClassName = L"momoka";

	RegisterClassEx(&wcex);

	ID2D1Factory* pDirect2DFactory;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2DFactory);
	pDirect2DFactory->GetDesktopDpi(&m_dpiX_, &m_dpiY_);
	SafeRelease(&pDirect2DFactory);

	m_windowWidth_ = static_cast<UINT>(ceil(m_windowWidth_ * m_dpiX_ / 96.f));
	m_windowHeight_ = static_cast<UINT>(ceil(m_windowHeight_ * m_dpiY_ / 96.f));

	m_hwnd_ = CreateWindow(
		L"momoka",
		m_appName_,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // posX
		CW_USEDEFAULT, // posY
		m_windowWidth_,
		m_windowHeight_,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	HRESULT hr = m_hwnd_ ? S_OK : E_FAIL;
	if (SUCCEEDED(hr)) {
		ShowWindow(m_hwnd_, SW_SHOWNORMAL);
		UpdateWindow(m_hwnd_);
		SetFocus(m_hwnd_);
		ShowCursor(true);
	}
}

WindowService::~WindowService() {
	ShowCursor(true);

	DestroyWindow(m_hwnd_);
	m_hwnd_ = nullptr;

	UnregisterClass(L"momoka", HINST_THISCOMPONENT);
}

LRESULT WindowService::WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {
	switch (umsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, umsg, wParam, lParam);
	}
}

HWND& WindowService::GetHwnd() {
	return m_hwnd_;
}

