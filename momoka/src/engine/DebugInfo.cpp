#include "stdafx.h"
#include "engine/DebugTools.h"
#include "engine/Engine.h"

DebugInfo::DebugInfo(): m_debugState_(0), m_lastF3Status_(false) {
}

bool DebugInfo::Draw() {
	if(m_debugState_ == 1) {
		const auto pEngineHandle = Engine::GetUniEngineHandle();
		if (pEngineHandle != nullptr) {
			auto pGraphicsTools = pEngineHandle->GetGraphicsTools();
			int fps = pEngineHandle->GetCurrentFps();
			WCHAR fpsInfo[16];
			wsprintf(fpsInfo, L"FPS: %d", fps);
			pGraphicsTools->Draw2DText(fpsInfo);
		}
	}

	return true;
}

bool DebugInfo::Update() {
	const auto pEngineHandle = Engine::GetUniEngineHandle();
	if (pEngineHandle != nullptr) {
		auto pInputTools = pEngineHandle->GetInputTools();
		if(pInputTools->GetKeyboardMessage(DIK_F3)) {
			if(!m_lastF3Status_) {
				m_debugState_ ^= 1;
				m_lastF3Status_ = true;
			}	
		}
		else {
			m_lastF3Status_ = false;
		}
	}
	return true;
}
