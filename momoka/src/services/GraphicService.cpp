#include "stdafx.h"
#include "services/GraphicService.h"

GraphicService* GraphicService::m_handle_ = nullptr;

GraphicService::GraphicService(): m_bufferLock_(true) {
	m_handle_ = this;
	CreateDeviceIndependentResources();
	InitializeWindow();
}

GraphicService::~GraphicService() {
	DiscardDeviceResources();
	KillWindow();
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

bool GraphicService::InitializeWindow() {
	m_appName_ = L"momoka";
	m_windowWidth_ = 1280;
	m_windowHeight_ = 720;

	WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
	wcex.lpszClassName = L"momoka";

	RegisterClassEx(&wcex);

	m_pDirect2DFactory_->GetDesktopDpi(&m_dpiX_, &m_dpiY_);

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

		// 创建m_pRenderTarget_
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
	// 销毁一切资源
	SafeRelease(&m_pDirect2DFactory_);
	SafeRelease(&m_pRenderTarget_);
	SafeRelease(&m_pDWriteFactory_);
	SafeRelease(&m_pCornflowerBlueBrush_);
	SafeRelease(&m_pWicFactory_);
}

void GraphicService::GetDpi(FLOAT& dpiX, FLOAT& dpiY) const {
	m_pDirect2DFactory_->GetDesktopDpi(&dpiX, &dpiY);
}

bool GraphicService::BeginDraw() {
	// 防止连续调用两次BeginDraw
	if (m_bufferLock_) {
		m_bufferLock_ = false;
		bool result;
		result = CreateDeviceResources();
		if (result) {
			m_pRenderTarget_->BeginDraw();
		}
		return result;
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

bool GraphicService::LoadBitMap(LPWSTR path, ID2D1Bitmap** ppBitmap) {
	// LoadBitmapFromFile();

	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pSource = nullptr;
	IWICStream* pStream = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	IWICBitmapScaler* pScaler = nullptr;

	hr = m_pWicFactory_->CreateDecoderFromFilename(
		path,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr)) {

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr)) {
		hr = m_pWicFactory_->CreateFormatConverter(&pConverter);
	}

	auto destinationWidth = 50;
	auto destinationHeight = 100;

	// If a new width or height was specified, create an
	// IWICBitmapScaler and use it to resize the image.
	if (destinationWidth != 0 || destinationHeight != 0) {
		UINT originalWidth, originalHeight;
		hr = pSource->GetSize(&originalWidth, &originalHeight);
		if (SUCCEEDED(hr)) {
			if (destinationWidth == 0) {
				FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
				destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
			}
			else if (destinationHeight == 0) {
				FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
				destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
			}

			hr = m_pWicFactory_->CreateBitmapScaler(&pScaler);
			if (SUCCEEDED(hr)) {
				hr = pScaler->Initialize(
					pSource,
					destinationWidth,
					destinationHeight,
					WICBitmapInterpolationModeCubic
				);
			}
			if (SUCCEEDED(hr)) {
				hr = pConverter->Initialize(
					pScaler,
					GUID_WICPixelFormat32bppPBGRA,
					WICBitmapDitherTypeNone,
					NULL,
					0.f,
					WICBitmapPaletteTypeMedianCut
				);
			}
		}
	}

	if (SUCCEEDED(hr)) {
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_pRenderTarget_->CreateBitmapFromWicBitmap(pConverter,
		                                                 nullptr,
		                                                 ppBitmap);
	}
	return false;
}

void GraphicService::DrawBitmap(ID2D1Bitmap* pBitmap) {

	m_pRenderTarget_->BeginDraw();

	// Clear background color to dark cyan
	// m_pRenderTarget_->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F size = pBitmap->GetSize();
	D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(0.f, 0.f);

	// Draw bitmap
	m_pRenderTarget_->DrawBitmap(
		pBitmap,
		D2D1::RectF(
			upperLeftCorner.x,
			upperLeftCorner.y,
			upperLeftCorner.x + size.width,
			upperLeftCorner.y + size.height)
	);

	HRESULT hr = m_pRenderTarget_->EndDraw();
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Draw failed!", L"Error", 0);

		return;
	}
}

void GraphicService::KillWindow() {
	ShowCursor(true);

	DestroyWindow(m_hwnd_);
	m_hwnd_ = nullptr;

	UnregisterClass(L"momoka", HINST_THISCOMPONENT);
}

void GraphicService::DrawRect(float x, float y, float width, float height) const {
	auto rect = D2D1::RectF(x, y, x + width, y + height);
	m_pRenderTarget_->FillRectangle(&rect, m_pCornflowerBlueBrush_);
}

void GraphicService::DrawTestWhiteBackGround() {
	m_pRenderTarget_->SetTransform(D2D1::Matrix3x2F::Identity());
	m_pRenderTarget_->Clear(D2D1::ColorF(D2D1::ColorF::White));
}


HWND& GraphicService::GetHwnd() {
	return m_hwnd_;
}


void GraphicService::OnResize(UINT width, UINT height) {
	m_windowHeight_ = height;
	m_windowWidth_ = width;
	if (m_pRenderTarget_) {
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget_->Resize(D2D1::SizeU(width, height));
	}
}

LRESULT GraphicService::WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) {
	switch (umsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 1;
	case WM_SIZE: {
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		m_handle_->OnResize(width, height);
	}
		return 0;
	case WM_DISPLAYCHANGE: {
		InvalidateRect(hwnd, nullptr, FALSE);
	}
		return 0;
	case WM_PAINT: {
		ValidateRect(hwnd, nullptr);
	}
		return 0;
	default:
		return DefWindowProc(hwnd, umsg, wParam, lParam);
	}
}
