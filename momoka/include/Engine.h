#pragma once
#include "stdafx.h"
#include "util/ServiceLoader.h"

class Engine {
public:
	Engine();
	~Engine();

	bool Initialize();
	void Shutdown();
	void Run();

	static LONGLONG m_freq;

private:
	ServiceLoader m_serviceLoader_;

};