#include "pch.h"
#include "CppUnitTest.h"
#include "D:\RB tree\RB tree\Map.h"
#include "D:\RB tree\RB tree\Map.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBTreeTests
{
	TEST_CLASS(RBTreeTests)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			Map <int, int> ar;
			Assert::IsTrue(ar.getSize() == 0);
		}

		TEST_METHOD(destroyTest)
		{
			Map<int, int> ar;
			ar.insert(10, 0);
			ar.insert(0, 0);
			ar.insert(20, 0);
			ar.destroy(ar.getHead()->right);
			Assert::IsTrue(ar.getHead()->right == nullptr);
		}

		TEST_METHOD(clearTest)
		{
			Map <int, int> ar;
			ar.insert(10, 0);
			ar.insert(14, 0);
			ar.insert(15, 0);
			ar.clear();
			Assert::IsTrue(ar.getSize() == 0 && ar.getHead() == nullptr);
		}

		TEST_METHOD(insertTest)
		{
			Map <int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			Assert::IsTrue(ar.getHead()->key == 50 && ar.getHead()->color == 0);
			Assert::IsTrue(ar.getHead()->right->key == 60 && ar.getHead()->right->color == 1);
		}

		TEST_METHOD(balanceInsertTest1)
		{
			Map<int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			ar.insert(40, 0);
			ar.insert(30, 0);

			Assert::IsTrue(ar.getHead()->key == 50 && ar.getHead()->color == 0);
			Assert::IsTrue(ar.getHead()->right->key == 60 && ar.getHead()->right->color == 0);
			Assert::IsTrue(ar.getHead()->left->key == 40 && ar.getHead()->left->color == 0);
			Assert::IsTrue(ar.getHead()->left->left->key == 30 && ar.getHead()->left->left->color == 1);
		}

		TEST_METHOD(balanceInsertTest2)
		{
			Map<int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			ar.getHead()->right->color = 0;
			ar.insert(40, 0);
			ar.insert(30, 0);
			Assert::IsTrue(ar.getHead()->key == 40 && ar.getHead()->color == 0);
			Assert::IsTrue(ar.getHead()->right->key == 50 && ar.getHead()->right->color == 1);
			Assert::IsTrue(ar.getHead()->left->key == 30 && ar.getHead()->left->color == 1);
			Assert::IsTrue(ar.getHead()->right->right->key == 60 && ar.getHead()->right->right->color == 0);
		}

		TEST_METHOD(removeTest)
		{
			Map<int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			ar.insert(40, 0);
			ar.insert(70, 0);
			ar.insert(55, 0);
			ar.insert(30, 0);
			ar.remove(60);
			Assert::IsTrue(ar.getSize() == 5);
		}

		TEST_METHOD(removeBalanceTest)
		{
			Map<int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			ar.insert(40, 0);
			ar.insert(70, 0);
			ar.insert(55, 0);
			ar.insert(30, 0);
			ar.remove(60);

			Assert::IsTrue(ar.getHead()->key == 50 && ar.getHead()->color == 0);
			Assert::IsTrue(ar.getHead()->right->key == 70 && ar.getHead()->right->color == 0);
			Assert::IsTrue(ar.getHead()->right->left->key == 55 && ar.getHead()->right->left->color == 1);
		}

		TEST_METHOD(leftRotateTest)
		{
			Map<int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			ar.insert(40, 0);
			ar.insert(70, 0);
			ar.insert(55, 0);
			ar.leftRotate(ar.getHead());

			Assert::IsTrue(ar.getHead()->key == 60 && ar.getHead()->left->key == 50 && ar.getHead()->left->left->key == 40 && 
				ar.getHead()->left->right->key == 55 && ar.getHead()->right->key == 70);
		}

		TEST_METHOD(rightRotateTest) {
			Map<int, int> ar;
			ar.insert(50, 0);
			ar.insert(60, 0);
			ar.insert(40, 0);
			ar.insert(45, 0);
			ar.insert(30, 0);
			ar.rightRotate(ar.getHead());

			Assert::IsTrue(ar.getHead()->key == 40 && ar.getHead()->left->key == 30 && ar.getHead()->right->key == 50 &&
				ar.getHead()->right->left->key == 45 && ar.getHead()->right->right->key == 60);
		}

		TEST_METHOD(getSizeTest) {
			Map<int, int> ar;
			ar.insert(20, 0);
			Assert::IsTrue(ar.getSize() == 1);
		}

		TEST_METHOD(getHeadTest) {
			Map<int, int> ar;
			ar.insert(20, 0);
			Assert::IsTrue(ar.getHead()->key == 20 && ar.getHead()->data == 0);
		}

		TEST_METHOD(findTest) {
			Map<int, int> ar;
			ar.insert(20, 0);
			ar.insert(21, 1);
			ar.insert(22, 2);
			ar.insert(23, 3);
			ar.insert(24, 4);
			ar.insert(25, 5);
			Assert::IsTrue(ar.find(23) == 3);
		}

		TEST_METHOD(getKeysTest) {
			Map<int, int> ar;
			std::list<int> keys;
			ar.insert(19, -1);
			ar.insert(20, 0);
			ar.insert(21, 1);
			ar.insert(22, 2);
			ar.insert(23, 3);
			ar.insert(24, 4);
			ar.remove(19);
			keys = ar.getKeys();
			Assert::IsTrue(std::find(keys.begin(), keys.end(), 20) != keys.end());
			Assert::IsTrue(std::find(keys.begin(), keys.end(), 21) != keys.end());
			Assert::IsTrue(std::find(keys.begin(), keys.end(), 22) != keys.end());
			Assert::IsTrue(std::find(keys.begin(), keys.end(), 23) != keys.end());
			Assert::IsTrue(std::find(keys.begin(), keys.end(), 24) != keys.end());
		}

		TEST_METHOD(getValuesTest) {
			Map<int, int> ar;
			std::list<int> values;
			ar.insert(19, -1);
			ar.insert(20, 0);
			ar.insert(21, 1);
			ar.insert(22, 2);
			ar.insert(23, 3);
			ar.insert(24, 4);
			ar.remove(19);
			values = ar.getValues();
			Assert::IsTrue(std::find(values.begin(), values.end(), 0) != values.end());
			Assert::IsTrue(std::find(values.begin(), values.end(), 1) != values.end());
			Assert::IsTrue(std::find(values.begin(), values.end(), 2) != values.end());
			Assert::IsTrue(std::find(values.begin(), values.end(), 3) != values.end());
			Assert::IsTrue(std::find(values.begin(), values.end(), 4) != values.end());
		}
	};
}
