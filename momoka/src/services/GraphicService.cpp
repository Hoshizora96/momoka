#include "stdafx.h"
#include "services/GraphicService.h"

GraphicService::GraphicService(HWND& hwnd) : m_hwnd_(hwnd),
                                             m_pDirect2DFactory_(nullptr),
                                             m_pDWriteFactory_(nullptr),
                                             m_pRenderTarget_(nullptr), m_bufferLock_(true) {

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

	if (SUCCEEDED(hr)) {
		hr = m_pRenderTarget_->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
			&m_pCornflowerBlueBrush_
		);
	}
	return SUCCEEDED(hr);
}

void GraphicService::DiscardDeviceResources() {
	SafeRelease(&m_pDirect2DFactory_);
	SafeRelease(&m_pRenderTarget_);
	SafeRelease(&m_pDWriteFactory_);
	SafeRelease(&m_pCornflowerBlueBrush_);
}

void GraphicService::GetDpi(FLOAT& dpiX, FLOAT& dpiY) const {
	m_pDirect2DFactory_->GetDesktopDpi(&dpiX, &dpiY);
}

bool GraphicService::BeginDraw() {
	// 防止连续调用两次BeginDraw
	if (m_bufferLock_) {
		m_bufferLock_ = false;
		HRESULT hr;
		hr = CreateDeviceResources();
		if (SUCCEEDED(hr)) {
			m_pRenderTarget_->BeginDraw();
		}
		return SUCCEEDED(hr);
	}
	else {
		// TODO: 添加调试信息
		return false;
	}
}

bool GraphicService::EndDraw() {
	// 防止连续调用两次EndDraw
	if (!m_bufferLock_) {
		m_bufferLock_ = true;
		HRESULT hr = m_pRenderTarget_->EndDraw();
		if (hr == D2DERR_RECREATE_TARGET) {
			hr = S_OK;
			DiscardDeviceResources();
		}
		return SUCCEEDED(hr);
	}
	else {
		// TODO: 添加调试信息
		return false;
	}
}

void GraphicService::DrawRect(float x, float y, float width, float height) const {
	m_pRenderTarget_->DrawRectangle(D2D1::RectF(x, y, x + width, y + height), m_pCornflowerBlueBrush_);
}
