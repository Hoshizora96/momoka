#include "stdafx.h"
#include "core/system/RenderSystem.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/GraphicService.h"

void RenderSystem::Update(float& dt, GameCore& core) {
	core.entityPool.Each<PlayerComponent>([&](GameEntityPool::Entity entity) {
		core.camera.LookAt(entity.Get<PositionComponent>()->x, entity.Get<PositionComponent>()->y);
	});
	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();
	graphicService->DrawTestWhiteBackGround();
	core.entityPool.Each<RenderComponent, PositionComponent>([&](GameEntityPool::Entity entity) {
		auto renderComp = entity.Get<RenderComponent>();
		auto positionComp = entity.Get<PositionComponent>();
		core.camera.DrawRect(positionComp->x, positionComp->y, renderComp->renderWidth, renderComp->renderHeight);
	});

	core.tilePool.Render(core.camera);
	graphicService->DrawBitmap(core.heroBitmap);
}
