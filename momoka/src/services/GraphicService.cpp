#include "stdafx.h"
#include "services/GraphicService.h"

GraphicService::GraphicService(HWND& hwnd) : m_hwnd_(hwnd),
                                             m_pDirect2DFactory_(nullptr),
                                             m_pDWriteFactory_(nullptr),
                                             m_pRenderTarget_(nullptr) {

}

GraphicService::~GraphicService() {
}

bool GraphicService::CreateDeviceIndependentResources() {
	HRESULT hr = S_OK;
	if (SUCCEEDED(hr)) {
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2DFactory_);
	}

	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory_));
	}

	return SUCCEEDED(hr);
}

bool GraphicService::CreateDeviceResources() {
	HRESULT hr = S_OK;
	if (!m_pRenderTarget_) {
		RECT rc;
		GetClientRect(m_hwnd_, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		hr = m_pDirect2DFactory_->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd_, size),
			&m_pRenderTarget_
		);
	}
	return SUCCEEDED(hr);
}

void GraphicService::DiscardDeviceResources() {
	SafeRelease(&m_pDirect2DFactory_);
	SafeRelease(&m_pRenderTarget_);
	SafeRelease(&m_pDWriteFactory_);
}

void GraphicService::GetDpi(FLOAT& dpiX, FLOAT& dpiY) const {
	m_pDirect2DFactory_->GetDesktopDpi(&dpiX, &dpiY);
}

bool GraphicService::BeginDraw() {
	HRESULT hr;
	hr = CreateDeviceResources();
	if (SUCCEEDED(hr)) {
		m_pRenderTarget_->BeginDraw();
	}

	return SUCCEEDED(hr);
}

bool GraphicService::EndDraw() {
	HRESULT hr = m_pRenderTarget_->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET) {
		hr = S_OK;
		DiscardDeviceResources();
	}
	return SUCCEEDED(hr);
}

