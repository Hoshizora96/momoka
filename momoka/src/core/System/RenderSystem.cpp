#include "stdafx.h"
#include "core/system/RenderSystem.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/GraphicService.h"

void RenderSystem::Update(float& dt, GameCore& core) {
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	graphicService->DrawTestWhiteBackGround();
	core.entityPool.Each<RenderComponent, PositionComponent>([&](GameEntityPool::Entity entity) {
		auto renderComp = entity.Get<RenderComponent>();
		auto positionComp = entity.Get<PositionComponent>();
		graphicService->DrawRect(positionComp->x, positionComp->y, renderComp->renderWidth, renderComp->renderHeight);
	});

	core.tilePool.Render();
}
