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

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam) const;

private:
	bool Frame();
	HRESULT InitializeWindow(UINT& screenWidth, UINT& screenHeight);
	void ShutdownWindow();

private:
	LPCWSTR m_applicationName_;
	HWND m_hwnd_;

	InputTools* m_pInputTools_;
	GraphicsTools* m_pGraphicsTools_;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

	static Engine* m_pApplicationHandle_;
};