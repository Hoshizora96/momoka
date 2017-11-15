#pragma once
class Renderable {
public:
	virtual ~Renderable() = default;
	virtual void Render(float dt) = 0;
};