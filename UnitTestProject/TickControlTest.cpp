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
		TickControl ticker;  // Single object for this class, so it's not safe to use it in more than one test method

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
			unsigned long start_tick = ticker.GetCurrentTick();
			if (start_tick != 0)
				Assert::Fail();
			// Else it succeeds automatically.

			ticker.Start();
			// Make sure the current tick is still the same as it was before starting. (Starting shouldn't increment the tick).
			unsigned long cur_tick = ticker.GetCurrentTick();
			Assert::AreSame(cur_tick, start_tick);
			
			// Increment tick , make sure they are different.
			cur_tick = ticker.Next();
			Assert::AreNotSame(cur_tick, start_tick);
			ticker.Stop();

			Assert::AreSame(cur_tick, ticker.GetCurrentTick());
		}

		TEST_METHOD(TestTickIncrementWithoutStart)
		{
			Assert::IsNotNull(pTicker);
			unsigned long start_tick = pTicker->GetCurrentTick();
			if (start_tick != 0)
				Assert::Fail();

			// Try incrementing the tick without Start()
			unsigned long cur_tick = pTicker->Next();
			Assert::AreSame(cur_tick, start_tick);

			// Try Starting and stopping the ticker, and then incrementing the tick
			pTicker->Start();
			cur_tick = pTicker->Next();
			Assert::AreNotSame(cur_tick, start_tick);
			pTicker->Stop();

			// Trying to increment tick when ticker is stopped...
			unsigned long new_tick = pTicker->Next();
			Assert::AreSame(new_tick, cur_tick);
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