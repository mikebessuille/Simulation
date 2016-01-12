#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>
#include "Simulation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{		
	TEST_CLASS(ThreadTest)
	{
	public:
		
		TEST_METHOD(TestSimulationClassCreation)
		{
			Simulation sim;
			sim.Start();
			sim.Stop();
			Assert::IsFalse(sim.IsRunning());
		}

		TEST_METHOD(TestSimulationStartStop)
		{
			Simulation sim;
			Assert::IsFalse(sim.IsRunning());
			sim.Start();
			Assert::IsTrue(sim.IsRunning());
			this_thread::sleep_for(chrono::seconds(3));
			Assert::IsTrue(sim.IsRunning());
			sim.Stop();
			this_thread::sleep_for(chrono::seconds(1));
			sim.Start();
			this_thread::sleep_for(chrono::seconds(2));
			Assert::IsTrue(sim.IsRunning());
			sim.Stop();
			Assert::IsFalse(sim.IsRunning());
		}

	};
}