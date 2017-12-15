#pragma once

class GameCore;
class System {
private:
	GameCore* core = nullptr;
public:
	virtual ~System();
	virtual void Update(float& dt, GameCore& core);
	virtual void SetGroup();
	virtual void Initialize(GameCore* m_core_);

};

inline System::~System() {
}

inline void System::Update(float& dt, GameCore& core) {
}

inline void System::SetGroup() {
	
}

inline void System::Initialize(GameCore* m_core_) {
	core = m_core_;
	SetGroup();
}

