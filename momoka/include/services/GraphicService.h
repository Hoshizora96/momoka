#pragma once
#include "stdafx.h"
#include "services/Service.h"

class GraphicService : public Service {
public:
	explicit GraphicService();
	~GraphicService();

	bool CreateDeviceIndependentResources();
	bool InitializeWindow();
	bool CreateDeviceResources();
	void DiscardDeviceResources();
	void GetDpi(FLOAT& dpiX, FLOAT& dpiY) const;
	bool BeginDraw();
	bool EndDraw();

	void KillWindow();

	HWND& GetHwnd();
	void OnResize(UINT width, UINT height);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

	void DrawRect(float x, float y, float width, float height) const;

private:
	// pointer
	ID2D1Factory* m_pDirect2DFactory_;
	IDWriteFactory* m_pDWriteFactory_;
	ID2D1HwndRenderTarget* m_pRenderTarget_;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush_;

	bool m_bufferLock_;

	HWND m_hwnd_;
	LPCWSTR m_appName_;
	FLOAT m_dpiX_;
	FLOAT m_dpiY_;
	UINT m_windowWidth_;
	UINT m_windowHeight_;

	static GraphicService* m_handle_;
};
