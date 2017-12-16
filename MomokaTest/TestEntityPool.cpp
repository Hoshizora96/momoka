#include "stdafx.h"
#include "CppUnitTest.h"
#include "core/object/EntityPool.h"
#include "core/object/components/BodyCollidableComponent.h"
#include "core/object/components/MoveComponent.h"
#include "core/object/components/PositionComponent.h"
#include "core/object/components/RenderComponent.h"
#include "core/object/components/WorldCollidableComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MomokaTest {
	TEST_CLASS(UnitTest1) {
	public:

		using TestPool = EntityPool<BodyCollidableComponent,
		                            MoveComponent,
		                            PositionComponent,
		                            RenderComponent,
		                            WorldCollidableComponent>;

	TEST_METHOD_INITIALIZE(SetUp) {
			Logger::WriteMessage("Test initialized.\n"); //���������Ϣ  
		}

	TEST_METHOD_CLEANUP(TearDown) {
			Logger::WriteMessage("Test completed.\n");
		}

		TEST_METHOD(TestCreateEmptyEntity) {
			TestPool pool;

			auto entity = pool.CreateEntity();
			Assert::IsTrue(entity.IsAlive(), L"entity������IsAlive()��Ϊtrue");
			auto entity2 = pool.CreateEntity();
			Assert::AreNotEqual(entity.GetIndex(), entity2.GetIndex(), L"�·����entityû�����entity����ͬһλ��");
		}

		TEST_METHOD(TestClearEntityComponentWhenCreateEmpty) {
			// �������ͨ�����µ�entity���䵽�ɵ�entityλ���������entity����ʱ�Ƿ���������ڿռ��ڵ����isActive�ֶ�
			TestPool pool;
			auto entity1 = pool.CreateEntity();

			entity1.Activate<PositionComponent>();
			entity1.Activate<BodyCollidableComponent>();
			entity1.Activate<MoveComponent>();
			entity1.Activate<RenderComponent>();
			entity1.Activate<WorldCollidableComponent>();
			const auto index = entity1.GetIndex();
			pool.DestroyEntity(entity1);

			auto entity2 = pool.CreateEntity();

			Assert::AreEqual(index, entity2.GetIndex(), L"�·����entityû�����entity����ͬһλ��");

			const auto noComponent = L"�ճ�ʼ��������ʵ�岻Ӧ�����κ����";
			Assert::IsFalse(entity2.Has<PositionComponent>(), noComponent);
			Assert::IsFalse(entity2.Has<BodyCollidableComponent>(), noComponent);
			Assert::IsFalse(entity2.Has<MoveComponent>(), noComponent);
			Assert::IsFalse(entity2.Has<RenderComponent>(), noComponent);
			Assert::IsFalse(entity2.Has<WorldCollidableComponent>(), noComponent);

		}

		TEST_METHOD(TestClearEntityComponentWhenCreate) {
			TestPool pool;
			auto entity1 = pool.CreateEntity();

			entity1.Activate<BodyCollidableComponent>();
			entity1.Activate<MoveComponent>();
			entity1.Activate<RenderComponent>();
			entity1.Activate<WorldCollidableComponent>();
			const auto index = entity1.GetIndex();
			pool.DestroyEntity(entity1);

			PositionComponent positionComponent;
			positionComponent.position = Vector2<float>(100, 100);
			auto entity2 = pool.CreateEntity(positionComponent);

			Assert::AreEqual(index, entity2.GetIndex(), L"�·����entityû�����entity����ͬһλ��");	

			Assert::IsTrue(entity2.Has<PositionComponent>());
			Assert::IsFalse(entity2.Has<BodyCollidableComponent>());
			Assert::IsFalse(entity2.Has<MoveComponent>());
			Assert::IsFalse(entity2.Has<RenderComponent>());
			Assert::IsFalse(entity2.Has<WorldCollidableComponent>());
		}

		TEST_METHOD(TestCreateEntityWithComponent) {
			TestPool pool;

			MoveComponent moveComponent;
			moveComponent.movingVelocity = 100;
			moveComponent.velocity = Vector2<float>(100, 100);

			PositionComponent positionComponent;
			positionComponent.position = Vector2<float>(100, 100);

			WorldCollidableComponent worldCollidableComponent;
			worldCollidableComponent.collisionBody = Vector2<float>(100, 100);

			auto entity = pool.CreateEntity(moveComponent, positionComponent, worldCollidableComponent);

			Assert::IsTrue(entity.IsAlive(), L"entity������IsAlive()��Ϊtrue");

			Assert::IsTrue(entity.Has<MoveComponent>());
			Assert::IsTrue(entity.Has<PositionComponent>());
			Assert::IsTrue(entity.Has<WorldCollidableComponent>());

			Assert::IsFalse(entity.Has<BodyCollidableComponent>());
			Assert::IsFalse(entity.Has<RenderComponent>());
		}

		TEST_METHOD(TestDestroyEntity) {
			TestPool pool;

			auto entity = pool.CreateEntity();
			Assert::AreEqual(entity.GetVersion(), EntityIndex(0));
			pool.DestroyEntity(entity);
			Assert::IsFalse(entity.IsAlive(), L"entity���ٺ�IsAlive()��Ϊfalse");

			auto entity2 = pool.CreateEntity();
			Assert::AreEqual(entity2.GetVersion(), EntityIndex(1));
			entity2.Destory();
			Assert::IsFalse(entity2.IsAlive(), L"entity���ٺ�IsAlive()��Ϊfalse");
		}

		TEST_METHOD(TestEntityComponentInterface) {
			TestPool pool;
			auto entity = pool.CreateEntity();
			entity.Activate<PositionComponent>();
			Assert::IsTrue(entity.Has<PositionComponent>(), L"������δ�ɹ�");

			entity.Disable<PositionComponent>();
			Assert::IsFalse(entity.Has<PositionComponent>(), L"ɾ�����δ�ɹ�");

			auto ptr1 = entity.Activate<BodyCollidableComponent>();
			auto ptr2 = entity.Get<BodyCollidableComponent>();
			Assert::IsTrue(ptr1 == ptr2);
		}

	};
}
