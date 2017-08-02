#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>
#include <memory>
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
			Game game; // Creates its own simulation but we can ignore it here as we're trying to test the Simulation object ONLY
			Simulation sim(&game);
			sim.Start();
			sim.Stop();
			Assert::IsFalse(sim.IsRunning());
		}

		TEST_METHOD(TestSimulationStartStop)
		{
			Game game;  // Creates its own simulation but we can ignore it here as we're trying to test the Simulation object ONLY
			Simulation sim(&game);
			
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


		TEST_METHOD(TestSimulationBadStartStop)
		{
			Game game;  // Creates its own simulation but we can ignore it here as we're trying to test the Simulation object ONLY
			Simulation sim(&game);

			Assert::IsFalse(sim.IsRunning());
			sim.Start();
			Assert::IsTrue(sim.IsRunning());
			sim.Start(); // Bad!  But we shouldn't fail...
			Assert::IsTrue(sim.IsRunning());
			this_thread::sleep_for(chrono::seconds(1));
			Assert::IsTrue(sim.IsRunning());
			sim.Stop();
			Assert::IsFalse(sim.IsRunning());
			sim.Stop(); // Bad!  But shouldn't fail
			Assert::IsFalse(sim.IsRunning());
		}

		void CreateSomeUsers(Game &g)
		{
			g.playerList.push_back(make_shared<Player>("Mike"));
			g.playerList.push_back(make_shared<Player>("Bob"));
			g.playerList.push_back(make_shared<Player>("Sally"));
		}


		// TODO: Move this to a separate GameTest class
		// TODO: add some units (like in UnitMgrTest.cpp)
		TEST_METHOD(TestGameCreation)
		{
			Game game;
			CreateSomeUsers(game);
			game.InitializeGame();
			int nNumUnitManagers = game.gs.UMList.size(); // gamestate is visible because we made this test class a friend of game and gamestate
			Assert::AreEqual( nNumUnitManagers, 3 );
		}

	};
}