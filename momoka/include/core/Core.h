#pragma once
class Core {
public:
	virtual ~Core() = default;
	virtual void Update(float& dt) = 0;
};