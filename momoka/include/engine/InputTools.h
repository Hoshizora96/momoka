#pragma once
#include "stdafx.h"

class InputTools {

private:
	HWND& m_hwnd_;

public:
	explicit InputTools(HWND& hwnd);

public:
	HRESULT Initialize();
	void Shutdown();
	bool GetKeyboardMessage(char* keyStateBuffer) const;
	bool GetMouseMessage(DIMOUSESTATE mouseState) const;

private:
	HRESULT KeyboardInitialize();
	HRESULT MouseInitialize();
	static HRESULT DeviceRead(IDirectInputDevice8* pDiDevice, void* pBuffer, long lSize);

private:
	LPDIRECTINPUT8 m_pDirectInput_;
	LPDIRECTINPUTDEVICE8 m_pMouseDevice_;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice_;
};

