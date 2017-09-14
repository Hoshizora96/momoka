#include "stdafx.h"
#include "services/InputService.h"


InputService::InputService(HWND& hwnd) : m_hwnd_(hwnd) {
	HRESULT hr = S_OK;
	hr = DirectInput8Create(
		HINST_THISCOMPONENT,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&m_pDirectInput_),
		nullptr
	);
	if (SUCCEEDED(hr)) {
		hr = MouseInitialize();
	}
	if (SUCCEEDED(hr)) {
		hr = KeyboardInitialize();
	}
}

InputService::~InputService() {
	SafeUnacquire(&m_pMouseDevice_);
	SafeUnacquire(&m_pKeyboardDevice_);

	SafeRelease(&m_pDirectInput_);
	SafeRelease(&m_pMouseDevice_);
	SafeRelease(&m_pKeyboardDevice_);
}

bool InputService::GetKeyboardMessage(UINT keyCode) const {
	return m_keyStateBuffer_[keyCode] & 0x80;
}

DIMOUSESTATE InputService::GetMouseMessage() const {
	return m_mouseState_;
}

void InputService::RefreshBuffer() {
	::ZeroMemory(m_keyStateBuffer_, sizeof(m_keyStateBuffer_));
	DeviceRead(m_pKeyboardDevice_, static_cast<LPVOID>(m_keyStateBuffer_), sizeof(m_keyStateBuffer_));

	::ZeroMemory(&m_mouseState_, sizeof(m_mouseState_));
	DeviceRead(m_pMouseDevice_, static_cast<LPVOID>(&m_mouseState_), sizeof(m_mouseState_));
}

bool InputService::KeyboardInitialize() {
	HRESULT hr = m_pDirectInput_->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice_, nullptr);

	if (SUCCEEDED(hr)) {
		m_pKeyboardDevice_->SetDataFormat(&c_dfDIKeyboard);
		m_pKeyboardDevice_->SetCooperativeLevel(m_hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		m_pKeyboardDevice_->Acquire();
	}

	return SUCCEEDED(hr);
}

bool InputService::MouseInitialize() {
	HRESULT hr = m_pDirectInput_->CreateDevice(GUID_SysMouse, &m_pMouseDevice_, nullptr);

	if (SUCCEEDED(hr)) {
		m_pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		m_pMouseDevice_->SetCooperativeLevel(m_hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		m_pMouseDevice_->Acquire();
	}

	return SUCCEEDED(hr);
}

bool InputService::DeviceRead(IDirectInputDevice8 * pDiDevice, void * pBuffer, long lSize) {
	HRESULT hr;
	while (true) {
		pDiDevice->Poll(); // 轮询设备  
		pDiDevice->Acquire(); // 获取设备的控制权  
		if (SUCCEEDED(hr = pDiDevice->GetDeviceState(lSize, pBuffer)))
			break;
		if (hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED)
			return false;
		if (FAILED(pDiDevice->Acquire()))
			return false;
	}
	return true;
}


