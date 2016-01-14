#include "stdafx.h"
#include "CppUnitTest.h"
#include "TickControl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
// namespace TickControlTest
{		
	TEST_CLASS(TickControlTest)
	{
	private:
		// Stuff that is setup by the class initializer; these must be static.
		static TickControl *pStaticTicker;	// Testing statics and CLASS_INITIALIZE.
		TickControl *pTicker; // use this in the Test Methods; non-static.
		TickControl ticker;

	public:
		TEST_CLASS_INITIALIZE(TickControlInit)
		{
			// Stuff that sets up all the tests in this class.  Only called once, and is static.  So, can't
			// reference non-static member variables of the class.
			pStaticTicker = new TickControl;
			Assert::IsNotNull(pStaticTicker);
			Assert::AreEqual((int)(pStaticTicker->GetCurrentTick()), 0);
		}

		TEST_CLASS_CLEANUP(TickControlCleanup)
		{
			Assert::IsNotNull(pStaticTicker);
			delete pStaticTicker;
			pStaticTicker = NULL;
		}

		// runs before each test
		TEST_METHOD_INITIALIZE(methodInit)
		{
			pTicker = new TickControl;
			Assert::IsNotNull(pTicker);
			Assert::AreEqual((int)(pTicker->GetCurrentTick()), 0);
		}

		// Runs after each test
		TEST_METHOD_CLEANUP(methodCleanup)
		{
			Assert::IsNotNull(pTicker);
			delete pTicker;
			pTicker = NULL;
		}

		TEST_METHOD(TestTickIncrement)
		{
			unsigned long cur_tick = ticker.GetCurrentTick();
			if (cur_tick != 0)
				Assert::Fail();
			// Else it succeeds automatically.
		}

		TEST_METHOD(TestTickDesignedToFail)
		{
			Assert::Fail();
		}

		TEST_METHOD(TestTickerPointers)
		{
			Assert::IsNotNull(pStaticTicker);
			// The pStaticTicker should have just been created so validate that the currentTick is 0.
			if (pStaticTicker->GetCurrentTick() != 0)
				Assert::Fail();

			Assert::IsNotNull(pTicker);
			// The pTicker should have just been created so validate that the currentTick is 0.
			if (pTicker->GetCurrentTick() != 0)
				Assert::Fail();
		}

	}; // end of TickControlTest class
	
	// need to provide definitions for the statics in the class
	TickControl * TickControlTest::pStaticTicker;

}