#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnitMgr.h"
#include "UnitBase.h"
#include "MoveComponent.h"
#include "GroundAttackComponentBasic.h"
#include "HealthComponentBasic.h"
#include "GameState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{
	TEST_CLASS(UnitAndComponentTest)
	{
		UnitBase * ConstructUnit(double x, double y, unsigned int damage, double range, unsigned int cooldown, unsigned int health )
		{
			shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic( damage, range, cooldown ));
			shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic( health ));
			return(new UnitBase(x, y, nullptr, acptr, hcptr));
		}


		void PopulateUnitsPlayer1(UnitMgr &UM )
		{
			// Create some units
			UM.AddUnit( ConstructUnit( 0, 0, 5, 10.0, 2, 12 ) );

			// Then assign them targets, so that they shoot at each other.
			// pUnit->GetAttackComponent()->AssignTarget();
		}

		void PopulateUnitsPlayer2(UnitMgr &UM)
		{

		}


		// Output the unit information to the test console
		void OutputUnitInfo( GameState &gs )
		{
			// TODO: Do this for each UM (one for each player)
			/*
			for (auto it : UM.unitList)
			{
				std::string message = "ID: " + to_string(it->id) + "	X: " + to_string(it->x) + "	Y: " + to_string(it->y) +
					" Health: " + to_string(it->GetHealthComponent()->CurrentHealth());
				const char * c_msg = message.c_str();
				Logger::WriteMessage(c_msg);
			}
			*/
		}


		void DoSomethingWithUnits( GameState &gs )
		{
			Logger::WriteMessage("Starting Unit Info:");
			OutputUnitInfo(gs);

			/*
			// TODO: go through each UM for each player...
			for (int nTick = 0; nTick < 10; nTick++)
			{
				for (auto &unit : UM.unitList)
				{
					unit->Update(gs, nTick);
				}
				Logger::WriteMessage("Unit Info after Tick: " + nTick );
				OutputUnitInfo(gs);
			}			
			*/
		}

		TEST_METHOD(TestUnitCreation)
		{
			UnitMgr UM_Player1;
			UnitMgr UM_Player2;

			PopulateUnitsPlayer1(UM_Player1);
			PopulateUnitsPlayer2(UM_Player2);

			GameState gs;

			gs.UMList.push_back(&UM_Player1);
			gs.UMList.push_back(&UM_Player2);

			DoSomethingWithUnits( gs );
		}

	}; // TEST Class "UnitAndComponentTest"
} // UnitTestProject namespace