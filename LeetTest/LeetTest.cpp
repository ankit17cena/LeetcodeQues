#include "pch.h"
#include "CppUnitTest.h"
#include "../LeetQues/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LeetTest
{
	TEST_CLASS(LeetTest)
	{
	public:

		TEST_METHOD(splitArraySameAverages)
		{
			Assert::IsTrue(splitArraySameAverage({ 1,2,3,4,5,6,7,8 }));

			Assert::IsFalse(splitArraySameAverage({ 3,1 }));
		}

		TEST_METHOD(cherryPickupa) {

			Assert::AreEqual(5, cherryPickup({ {0,1,-1},{1,0,-1},{1,1,1} }));

			Assert::AreEqual(0, cherryPickup({ {1,1,-1},{1,-1,1},{-1,1,1} }));

		}

		TEST_METHOD(minDay) {

			Assert::AreEqual(4, minDays(10));

			Assert::AreEqual(3, minDays(6));

		}

		TEST_METHOD(minimumCosts) {

			ll actual = minimumCost("0011");
			ll expected = 2;
			Assert::AreEqual(expected, actual);

			actual = minimumCost("010101");
			expected = 9;
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(maxSums) {

			std::vector<int>v1 = { 2,4,5,8,10 };
			std::vector<int>v2 = { 4,6,8,9 };
			Assert::AreEqual(30, maxSum(v1, v2));


			v1 = { 1,3,5,7,9 };
			v2 = { 3,5,100 };
			Assert::AreEqual(109, maxSum(v1, v2));

			v1 = { 1,2,3,4,5 };
			v2 = { 6,7,8,9,10 };
			Assert::AreEqual(40, maxSum(v1, v2));
		}

		TEST_METHOD(nextPermutations) {

			std::vector<int>actual = nextPermutation({ 1,2,3 });
			std::vector<int>expected = { 1,3,2 };
			for (int j = 0; j < expected.size(); j++) {
				Assert::AreEqual(expected[j], actual[j]);
			}

			actual = nextPermutation({ 1,1,5 });
			expected = { 1,5,1 };
			for (int j = 0; j < expected.size(); j++) {
				Assert::AreEqual(expected[j], actual[j]);
			}

			actual = nextPermutation({ 3,2,1 });
			expected = { 1,2,3 };
			for (int j = 0; j < expected.size(); j++) {
				Assert::AreEqual(expected[j], actual[j]);
			}
		}

		TEST_METHOD(canSeePersonsCounts) {

			std::vector<int>actual = canSeePersonsCount({ 10,6,8,5,11,9 });
			std::vector<int>expected = { 3,1,2,1,1,0 };
			Assert::AreEqual(expected.size(), actual.size());
			for (int j = 0; j < expected.size(); j++) {
				Assert::AreEqual(expected[j], actual[j]);
			}

			actual = canSeePersonsCount({ 5,1,2,3,10 });
			expected = { 4,1,1,1,0 };
			Assert::AreEqual(expected.size(), actual.size());
			for (int j = 0; j < expected.size(); j++) {
				Assert::AreEqual(expected[j], actual[j]);
			}
		}

		TEST_METHOD(totalFruits) {

			std::vector<int>v = { 0,1,2,2 };
			Assert::AreEqual(3, totalFruit(v));

			v = { 1,2,3,2,2 };
			Assert::AreEqual(4, totalFruit(v));

		}
	};
}
