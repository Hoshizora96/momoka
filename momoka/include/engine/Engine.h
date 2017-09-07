#pragma once
#include "stdafx.h"
#include "InputTools.h"
#include "GraphicsTools.h"

class Engine {
public:
	Engine();

public:
	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	HRESULT InitializeWindow(UINT &screenWidth, UINT &screenHeight);
	void ShutdownWindow();

private:
	LPCWSTR m_applicationName;
	HWND m_hwnd;

	InputTools *m_pInputTools;
	GraphicsTools *m_pGraphicsTools;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

	static Engine* ApplicationHandle;
};


#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif