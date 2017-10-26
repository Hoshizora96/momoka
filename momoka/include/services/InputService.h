#pragma once
#include "stdafx.h"
#include "services/Service.h"

// down表示按键持续按下，release表示松开按键的动作，press表示按下按键的动作
enum INPUT_KEY_EVENT {
	Key_down, Key_release, Key_press
};

class InputService : public Service {
public:
	explicit InputService(HWND& hwnd);
	~InputService();
	bool IsKeyEventHappened(UINT keyCode, INPUT_KEY_EVENT keyEvent = Key_down) const;
	DIMOUSESTATE GetMouseMessage() const;
	void RefreshBuffer();

private:
	HWND& m_hwnd_;
	LPDIRECTINPUT8 m_pDirectInput_;
	LPDIRECTINPUTDEVICE8 m_pMouseDevice_;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice_;

	char m_currentKeyStateBuffer_[256];
	char m_preKeyStateBuffer_[256];
	DIMOUSESTATE m_mouseState_;

	bool KeyboardInitialize();
	bool MouseInitialize();
	static bool DeviceRead(IDirectInputDevice8* pDiDevice, void* pBuffer, long lSize);
};
