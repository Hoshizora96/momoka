#pragma once

class DebugInfo {
	int m_debugState_;
	bool m_lastF3Status_;

public:
	explicit DebugInfo();

	bool Draw();
	bool Update();
};
