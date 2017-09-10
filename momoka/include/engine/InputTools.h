#pragma once
#include "stdafx.h"

class InputTools {
	HWND& m_hwnd_;
	LPDIRECTINPUT8 m_pDirectInput_;
	LPDIRECTINPUTDEVICE8 m_pMouseDevice_;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice_;

public:
	explicit InputTools(HWND& hwnd);

	HRESULT Initialize();
	void Shutdown();
	bool GetKeyboardMessage(UINT keyCode) const;
	DIMOUSESTATE GetMouseMessage() const;
	void Update();

private:
	HRESULT KeyboardInitialize();
	HRESULT MouseInitialize();
	static HRESULT DeviceRead(IDirectInputDevice8* pDiDevice, void* pBuffer, long lSize);

	char m_keyStateBuffer_[256];
	DIMOUSESTATE m_mouseState_;

};
