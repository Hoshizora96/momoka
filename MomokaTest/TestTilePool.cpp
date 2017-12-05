#include "stdafx.h"
#include "CppUnitTest.h"
#include "core/map/TilePool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MomokaTest {
	TEST_CLASS(UnitTest2) {
	public:


	TEST_METHOD_INITIALIZE(SetUp) {
			Logger::WriteMessage("Test initialized.\n"); //用于输出信息  
		}

	TEST_METHOD_CLEANUP(TearDown) {
			Logger::WriteMessage("Test completed.\n");
		}

		TEST_METHOD(TestTileHashConvert) {
			TilePool pool;
			pool.LoadConfig("H:/Project/momoka/momoka/momoka/content/tiles/tile-type-test.json");
			pool.AddTile(1, 1, 0);
			Assert::AreEqual(size_t(1), pool.Count());
			Assert::IsTrue(pool.HasTile(1,1));
			Assert::IsTrue(pool.GetType(1, 1) != nullptr);
			Assert::IsTrue(pool.GetType(1, 1)->GetId() == 0);
		}
	};
}
