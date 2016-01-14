#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NewTestClass
{		
	TEST_CLASS(NewTestClass)
	{
	public:
		TEST_METHOD(TestMethod3)
		{
			// TODO: Your test code here
			int i = 3;
			int j = 4;
			//Assert::NotEqual(i, j);
		}
	};
}