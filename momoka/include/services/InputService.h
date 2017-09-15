#pragma once
#include "stdafx.h"
#include "services/Service.h"

class InputService : public Service {
public:
	explicit InputService(HWND& hwnd);
	~InputService();
	bool IsKeyPressed(UINT keyCode) const;
	DIMOUSESTATE GetMouseMessage() const;
	void RefreshBuffer();

private:
	HWND& m_hwnd_;
	LPDIRECTINPUT8 m_pDirectInput_;
	LPDIRECTINPUTDEVICE8 m_pMouseDevice_;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice_;

	char m_keyStateBuffer_[256];
	DIMOUSESTATE m_mouseState_;

	bool KeyboardInitialize();
	bool MouseInitialize();
	static bool DeviceRead(IDirectInputDevice8* pDiDevice, void* pBuffer, long lSize);
};

