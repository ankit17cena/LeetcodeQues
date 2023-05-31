#include "pch.h"
#include "CppUnitTest.h"
#include "../LeetQues1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LeetTest1
{
	TEST_CLASS(LeetTest1)
	{
	public:
		
		TEST_METHOD(findMaxConsecutiveOne)
		{
			std::vector<int>v = { 1,1,0,1,1,1 };
			Assert::AreEqual(3, findMaxConsecutiveOnes(v));

			v = { 1,0,1,1,0,1 };
			Assert::AreEqual(2, findMaxConsecutiveOnes(v));

		}

		TEST_METHOD(maxProductPaths)
		{
			Assert::AreEqual(-1, maxProductPath({ {-1, -2, -3},{-2, -3, -3},{-3, -3, -2} }));

			Assert::AreEqual(8, maxProductPath({ {1,-2,1} ,{1,-2,1},{3,-4,1} }));

			Assert::AreEqual(0, maxProductPath({ {1,3} ,{0,-4} }));


		}

		TEST_METHOD(maximumMinute)
		{
			Assert::AreEqual(3, maximumMinutes({ {0,2,0,0,0,0,0} ,{0,0,0,2,2,1,0},{0,2,0,0,1,2,0},{0,0,2,2,2,0,2},{0,0,0,0,0,0,0} }));

			Assert::AreEqual(-1, maximumMinutes({ {0,0,0,0 }, { 0,1,2,0 }, { 0,2,0,0 }}));

			Assert::AreEqual(1000000000, maximumMinutes({ {0,0,0} ,{2,2,0},{1,2,0} }));
		}

		TEST_METHOD(equalSubstrings)
		{
			int actual = equalSubstring("abcd","bcdf",3);
			int expected = 3;
			Assert::AreEqual(expected, actual);

			actual = equalSubstring("abcd","cdef",3);
			expected = 1;
			Assert::AreEqual(expected, actual);

			actual = equalSubstring("abcd","acde", 0);
			expected = 1;
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(swimInWater1)
		{
			Assert::AreEqual(3, swimInWater({ {0,2 }, { 1,3 }}));

			Assert::AreEqual(16, swimInWater({ {0,1,2,3,4} ,{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6} }));
		}

		 
		TEST_METHOD(minimizeTheDifferences)
		{
			//std::vector<std::vector<int>>& v = { {1, 2, 3},{4, 5, 6},{7, 8, 9} };
			Assert::AreEqual(0, minimizeTheDifference({ {1, 2, 3},{4, 5, 6},{7, 8, 9} }, 13));

			//v = { {1},{2},{3} };
			Assert::AreEqual(94, minimizeTheDifference({ {1},{2},{3} }, 100));

			//v = { {1,2,9,8,7 } };
			Assert::AreEqual(1, minimizeTheDifference({ {1,2,9,8,7 } }, 6));

		}

		TEST_METHOD(minInsertion)
		{
			int actual = minInsertions("zzazz");
			int expected = 0;
			Assert::AreEqual(expected, actual);

			actual = minInsertions("mbadm");
			expected = 2;
			Assert::AreEqual(expected, actual);

			actual = minInsertions("leetcode");
			expected = 5;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(numDecoding)
		{
			int actual = numDecodings("12");
			int expected = 2;
			Assert::AreEqual(expected, actual);

			actual = numDecodings("226");
			expected = 3;
			Assert::AreEqual(expected, actual);

		}
	};
}
