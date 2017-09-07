#pragma once
#include "stdafx.h"

class GraphicsTools {

public:
	GraphicsTools();
	~GraphicsTools();

public:
	HRESULT Initialize(const HWND& hwnd);
	void Shutdown();

	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void GetDpi(FLOAT &dpiX, FLOAT &dpiY);

private:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
};

/*
设备独立资源包括：

ID2D1DrawingStateBlock
ID2D1Factory
ID2D1Geometry 和由此继承而来的接口
ID2D1GeometrySink and ID2D1SimplifiedGeometrySink
ID2D1StrokeStyle
设备依赖资源包括：

ID2D1Brush 和由此继承而来的接口
ID2D1Layer
ID2D1RenderTarget 和由此继承而来的接口
其他资源
*/