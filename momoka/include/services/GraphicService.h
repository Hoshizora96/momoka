#pragma once
#include "stdafx.h"
#include "services/Service.h"

class GraphicService :public Service {
public:
	explicit GraphicService(HWND& hwnd);
	~GraphicService();

	bool CreateDeviceIndependentResources();
	bool CreateDeviceResources();
	void DiscardDeviceResources();
	void GetDpi(FLOAT &dpiX, FLOAT &dpiY) const;
	bool BeginDraw();
	bool EndDraw();

private:
	HWND& m_hwnd_;  // 通过引用绑定WindowService中的m_hwnd_
	ID2D1Factory* m_pDirect2DFactory_;
	IDWriteFactory* m_pDWriteFactory_;
	ID2D1HwndRenderTarget* m_pRenderTarget_;
};
