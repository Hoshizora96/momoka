#pragma once
#include "stdafx.h"
#include "InputTools.h"
#include "GraphicsTools.h"
#include "engine/DebugTools.h"

class Engine {
public:
	Engine();

	bool Initialize();
	void Shutdown();
	void Run();

	int GetCurrentFps() const;
	int GetExpectFps() const;
	
	InputTools* GetInputTools() const;
	GraphicsTools* GetGraphicsTools() const;

	static const Engine* GetUniEngineHandle();

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
	DebugInfo* m_pDebugInfo_;
};