#include "stdafx.h"
#include "CppUnitTest.h"
#include "TickControl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{		
	TEST_CLASS(TickControlTest)
	{
	public:
		TEST_CLASS_INITIALIZE(TickControlInit)
		{
			// Stuff that sets up all the tests in this class.  Only called once.
			/*
			// Can't do any of this, because TickControl isn't exported from my DLL.
			// Would have to move these tests to be part of the SimulationDLL project.
			pTicker = new TickControl;
			Assert::IsNotNull(pTicker);
			Assert::AreEqual((int)(pTicker->GetCurrentTick()), 0);
			*/
		}

		TEST_METHOD(TestTickIncrement)
		{
		}

		TEST_CLASS_CLEANUP(TickControlCleanup)
		{
			//Assert::IsNotNull(pTicker);
			// delete pTicker;
		}

	private:
		// Stuff that is setup by the class initializer
		//static TickControl *pTicker;
	};
}