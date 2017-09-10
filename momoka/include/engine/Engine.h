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
	int GetCurrentFps() const;
	int GetExpectFps() const;

private:
	bool Frame();
	bool Update();
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

	HRESULT InitializeWindow(UINT& screenWidth, UINT& screenHeight);
	void ShutdownWindow();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam);

private:
	LPCWSTR m_applicationName_;
	HWND m_hwnd_;

	InputTools* m_pInputTools_;
	GraphicsTools* m_pGraphicsTools_;
	
	LONGLONG m_tickForDrawFrame_;
	LONGLONG m_tickForCountFrame_;
	LONGLONG m_freq_;

	int m_currentFps_;
	int m_frame_;

	const FLOAT m_expectFps_ = 60.0f;

	static Engine* m_pUniEngineHandle_;

	// TODO: 把测试的部分分离出去
	WCHAR m_fpsStr_[40] = {0};

	float m_posX_;
	float m_posY_;
};