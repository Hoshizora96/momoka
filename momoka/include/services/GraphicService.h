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

	bool LoadBitMap(LPWSTR path);

	void KillWindow();

	HWND& GetHwnd();
	void OnResize(UINT width, UINT height);
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

	void DrawRect(float x, float y, float width, float height) const;

	void DrawTestWhiteBackGround();


private:
	// 首先初始化要在声明时就做，反正都是nullptr

	// 这是一个设备无关资源，用来创建基本的direct2d绘图工具
	ID2D1Factory* m_pDirect2DFactory_ = nullptr;

	// 这是一个设备无关资源，用来创建direct2d文字绘制工具
	IDWriteFactory* m_pDWriteFactory_ = nullptr;

	// 这是一个设备相关资源，用来向窗口绘制图形图像
	ID2D1HwndRenderTarget* m_pRenderTarget_ = nullptr;

	// 这是一个设备相关资源，蓝色笔刷
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush_ = nullptr;

	IWICImagingFactory2* m_pWicFactory_ = nullptr;

	bool m_bufferLock_;

	HWND m_hwnd_;
	LPCWSTR m_appName_;
	FLOAT m_dpiX_;
	FLOAT m_dpiY_;
	UINT m_windowWidth_;
	UINT m_windowHeight_;

	static GraphicService* m_handle_;
};
