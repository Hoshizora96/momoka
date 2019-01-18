#include "stdafx.h"
#include "core/system/RenderSystem.h"
#include "core/GameCore.h"
#include "Engine.h"
#include "services/GraphicService.h"

void RenderSystem::PlayAnimation(GameEntityPool::Entity& entity, float dt) {
	auto animationComp = entity.Get<AnimationComponent>();
	animationComp->animationPlayedTime += dt;
	if(entity.Has<PlayerComponent, PositionComponent, VelocityComponent>()) {
		auto positionComp = entity.Get<PositionComponent>();
		auto newPosition = core->camera.TransformedCoordinate(positionComp->x, positionComp->y);
		auto playerComp = entity.Get<PlayerComponent>();
		core->heroAnimator.Play(animationComp->animationPlayedTime, animationComp->animationType, newPosition.GetX(), newPosition.GetY(), playerComp->direction);
	}
}

void RenderSystem::Update(float& dt) {

	// 将相机视角对准玩家
	core->entityPool.Each<PlayerComponent>([&](GameEntityPool::Entity entity) {
		core->camera.LookAt(entity.Get<PositionComponent>()->x, entity.Get<PositionComponent>()->y);
	});


	auto graphicService = Engine::serviceLoader.LocateService<GraphicService>(Service_graphic).lock();

	// 背景绘制
	graphicService->DrawTestWhiteBackGround();

	// 绘制图形
	core->entityPool.Each<RenderComponent, PositionComponent>([&](GameEntityPool::Entity entity) {
		auto renderComp = entity.Get<RenderComponent>();
		auto positionComp = entity.Get<PositionComponent>();
		core->camera.DrawRect(positionComp->x, positionComp->y, renderComp->renderWidth, renderComp->renderHeight);
	});

	// 绘制动画
	auto& animationEntities = core->groupManager.GetGroup<groups::AnimatorGroup>();
	for(int i = 0; i < animationEntities.Size(); i++) {
		auto entity = animationEntities[i];
		PlayAnimation(entity, dt);
	}

	// 绘制砖块
	core->tilePool.Render(core->camera);

	// 绘制测试图
	graphicService->DrawBitmap(core->heroBitmap);
	
}

std::string RenderSystem::toString() {
	return std::string("render system");
}
