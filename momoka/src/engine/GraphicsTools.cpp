#include "stdafx.h"
#include "engine/GraphicsTools.h"

// TODO: 先令这部分跑起来

GraphicsTools::GraphicsTools(HWND& hwnd) : m_hwnd_(hwnd),
                                           m_pDirect2DFactory_(nullptr),
                                           m_pDWriteFactory_(nullptr),
                                           m_pRenderTarget_(nullptr),
                                           m_pLightSlateGrayBrush_(nullptr),
                                           m_pCornflowerBlueBrush_(nullptr),
                                           m_pITextFormat_(nullptr) {
}

GraphicsTools::~GraphicsTools() {
}

HRESULT GraphicsTools::Initialize() {
	HRESULT hr;
	hr = CreateDeviceIndependentResources();

	return hr;
}

void GraphicsTools::Shutdown() {
	DiscardDeviceResources();
}

HRESULT GraphicsTools::CreateDeviceIndependentResources() {
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

	return hr;
}

HRESULT GraphicsTools::CreateDeviceResources() {
	// 利用m_pDirect2dFactory创建设备依赖资源

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

		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget_->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&m_pCornflowerBlueBrush_
			);
		}

		if (SUCCEEDED(hr)) {
			hr = m_pRenderTarget_->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&m_pLightSlateGrayBrush_
			);
		}

		if (SUCCEEDED(hr)) {
			hr = m_pDWriteFactory_->CreateTextFormat(
				L"Arial",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				10.0f * 96.0f / 72.0f,
				L"en-US",
				&m_pITextFormat_
			);
		}
	}
	return hr;
}

void GraphicsTools::DiscardDeviceResources() {
	SafeRelease(&m_pDirect2DFactory_);
	SafeRelease(&m_pRenderTarget_);
	SafeRelease(&m_pDWriteFactory_);
	SafeRelease(&m_pITextFormat_);
	SafeRelease(&m_pLightSlateGrayBrush_);
	SafeRelease(&m_pCornflowerBlueBrush_);
}

void GraphicsTools::GetDpi(FLOAT& dpiX, FLOAT& dpiY) const {
	m_pDirect2DFactory_->GetDesktopDpi(&dpiX, &dpiY);
}

HRESULT GraphicsTools::DrawDemo() const {
	HRESULT hr = S_OK;

	m_pRenderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pRenderTarget_->Clear(D2D1::ColorF(D2D1::ColorF::White));
	D2D1_SIZE_F rtSize = m_pRenderTarget_->GetSize();

	int width = static_cast<int>(rtSize.width);
	int height = static_cast<int>(rtSize.height);

	for (int x = 0; x < width; x += 10) {
		m_pRenderTarget_->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
			m_pLightSlateGrayBrush_,
			0.5f
		);
	}

	for (int y = 0; y < height; y += 10) {
		m_pRenderTarget_->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
			m_pLightSlateGrayBrush_,
			0.5f
		);
	}

	return hr;
}

bool GraphicsTools::Draw2DText(WCHAR* text) {
	D2D1_RECT_F layoutRect = D2D1::RectF(0.f, 0.f, 100.f, 100.f);
	m_pRenderTarget_->DrawText(
		text,
		wcslen(text),
		m_pITextFormat_,
		layoutRect,
		m_pCornflowerBlueBrush_
	);

	return true;
}


void GraphicsTools::OnResize(UINT width, UINT height) const {
	if (m_pRenderTarget_) {
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget_->Resize(D2D1::SizeU(width, height));
	}
}

HRESULT GraphicsTools::BeginDraw() {
	HRESULT hr;
	hr = CreateDeviceResources();
	if (SUCCEEDED(hr)) {
		m_pRenderTarget_->BeginDraw();
	}

	return hr;
}

HRESULT GraphicsTools::EndDraw() {
	HRESULT hr = m_pRenderTarget_->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET) {
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
}
