#pragma once
#include "components/Camera.h"
class Renderable {
public:
	virtual ~Renderable() = default;
	virtual void Render(float dt, Camera* camera = nullptr) = 0;
};