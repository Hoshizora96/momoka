#pragma once
#include "stdafx.h"
#include "services/Service.h"

class WindowService : public Service {
public:
	explicit WindowService(LPCWSTR appName);
	~WindowService();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);
	HWND& GetHwnd();
private:
	HWND m_hwnd_;
	LPCWSTR m_appName_;
	FLOAT m_dpiX_;
	FLOAT m_dpiY_;
	UINT m_windowWidth_;
	UINT m_windowHeight_;
};
