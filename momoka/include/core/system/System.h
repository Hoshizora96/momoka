#pragma once
#include <string>

class GameCore;
class System {
protected:
	GameCore* core = nullptr;
	
public:
	virtual ~System();
	virtual void Update(float& dt);

	void Initialize(GameCore* m_core_);

	virtual std::string toString();
};

inline System::~System() {
}

inline void System::Update(float& dt) {
}

inline void System::Initialize(GameCore* m_core_) {
	core = m_core_;
}

inline std::string System::toString() {
	return std::string("undefined system");
}

