#pragma once
#include "mixin/Renderable.h"
#include "mixin/Updatable.h"


class World : public Renderable, public Updatable {

public:
	void Render(float dt) override;
	void Update(float dt) override;
};
