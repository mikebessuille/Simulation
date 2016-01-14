#include "stdafx.h"
#include "CppUnitTest.h"
#include "TickControl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
// namespace TickControlTest
{		
	TEST_CLASS(TickControlTest)
	{
	public:
	//private:
		// Stuff that is setup by the class initializer
		//static TickControl *pTicker;
		// TickControl *pTicker;
		TickControl ticker;

	public:
		TEST_CLASS_INITIALIZE(TickControlInit)
		{
			// Stuff that sets up all the tests in this class.  Only called once.
			// Can't do any of this if Simulation build as a DLL, because TickControl isn't exported from my DLL.
			// Would have to move these tests to be part of the SimulationDLL project.
			/*
			pTicker = new TickControl;
			Assert::IsNotNull(pTicker);
			Assert::AreEqual((int)(pTicker->GetCurrentTick()), 0);
			*/
		}

		TEST_METHOD(TestTickIncrement)
		{
			//Assert::AreEqual(3, 4);
			unsigned long cur_tick = ticker.GetCurrentTick();
			if (cur_tick != 0)
				Assert::Fail();
			//else
				// Assert::Succeed(); Is there a succeed method?
		}

		TEST_METHOD(TestTickDesignedToFail)
		{
			Assert::Fail();
		}

		TEST_CLASS_CLEANUP(TickControlCleanup)
		{
			/*
			Assert::IsNotNull(pTicker);
			delete pTicker;
			*/
		}

	};
}