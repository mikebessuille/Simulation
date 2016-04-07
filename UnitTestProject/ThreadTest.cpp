#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>
#include "Simulation.h"
#include "Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{		
	TEST_CLASS(ThreadTest)
	{
	public:
		
		TEST_METHOD(TestSimulationClassCreation)
		{
			Game game;
			game.sim.Start();
			game.sim.Stop();
			Assert::IsFalse(game.sim.IsRunning());
		}

		TEST_METHOD(TestSimulationStartStop)
		{
			Game game;
			Assert::IsFalse(game.sim.IsRunning());
			game.sim.Start();
			Assert::IsTrue(game.sim.IsRunning());
			this_thread::sleep_for(chrono::seconds(3));
			Assert::IsTrue(game.sim.IsRunning());
			game.sim.Stop();
			this_thread::sleep_for(chrono::seconds(1));
			game.sim.Start();
			this_thread::sleep_for(chrono::seconds(2));
			Assert::IsTrue(game.sim.IsRunning());
			game.sim.Stop();
			Assert::IsFalse(game.sim.IsRunning());
		}

	};
}