#include "stdafx.h"
#include "GraphicsTools.h"


GraphicsTools::GraphicsTools() :
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL) {
}

GraphicsTools::~GraphicsTools() {
}

HRESULT GraphicsTools::Initialize(const HWND& hwnd) {
	HRESULT hr;
	hr = CreateDeviceIndependentResources();
	return hr;
}

void GraphicsTools::Shutdown() {
}

HRESULT GraphicsTools::CreateDeviceIndependentResources() {
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	return hr;
}

HRESULT GraphicsTools::CreateDeviceResources() {

	// 利用m_pDirect2dFactory创建设备依赖资源

	HRESULT hr = S_OK;

	if (!m_pRenderTarget) {
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);
	}
	return hr;
}

void GraphicsTools::DiscardDeviceResources() {
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
}

void GraphicsTools::GetDpi(FLOAT & dpiX, FLOAT & dpiY) {
	m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
}
