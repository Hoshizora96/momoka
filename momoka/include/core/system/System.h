#pragma once

class GameCore;
class System {
public:
	virtual ~System() = default;
	virtual void Update(float& dt, GameCore& core) = 0;
};