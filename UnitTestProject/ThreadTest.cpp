#include "stdafx.h"
#include "CppUnitTest.h"

#include "Simulation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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

	};
}