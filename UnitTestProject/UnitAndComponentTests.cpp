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
		// This test method acts like a factory
		UnitBase * ConstructUnit(double x, double y, unsigned int damage, double range, unsigned int cooldown, unsigned int health )
		{
			shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic( damage, range, cooldown ));
			shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic( health ));
			return(new UnitBase(x, y, nullptr, acptr, hcptr));
		}


		void PopulateUnits(UnitMgr &UM1, UnitMgr &UM2)
		{
			// Create some units for Player 1
			UnitBase *P1[5];
			P1[0] = ConstructUnit(0, 0, 5, 10.0, 2, 12);
			P1[1] = ConstructUnit(0, 1, 5, 10.0, 2, 12);
			P1[2] = ConstructUnit(1, 1, 5, 10.0, 2, 12);
			P1[3] = ConstructUnit(1, 2, 5, 10.0, 2, 12);
			P1[4] = ConstructUnit(2, 1, 5, 10.0, 2, 12);

			for (int i = 0; i < 5; ++i)
			{
				UM1.AddUnit(P1[i]);
			}

			// Create some units for Player 2
			UnitBase *P2[5];
			P2[0] = ConstructUnit(5, 5, 5, 10.0, 2, 12);
			P2[1] = ConstructUnit(5, 4, 5, 10.0, 2, 12);
			P2[2] = ConstructUnit(4, 5, 5, 10.0, 2, 12);
			P2[3] = ConstructUnit(4, 4, 5, 10.0, 2, 12);
			P2[4] = ConstructUnit(4, 3, 5, 10.0, 2, 12);

			for (int i = 0; i < 5; ++i)
			{
				UM2.AddUnit(P2[i]);
			}

			// Then assign them targets, so that they shoot at each other.
			P1[0]->GetAttackComponent()->AssignTarget(P2[0]);
			P1[1]->GetAttackComponent()->AssignTarget(P2[1]);
			P1[2]->GetAttackComponent()->AssignTarget(P2[1]);
			P1[3]->GetAttackComponent()->AssignTarget(P2[4]);

			P2[0]->GetAttackComponent()->AssignTarget(P1[3]);
			P2[1]->GetAttackComponent()->AssignTarget(P1[4]);
			P2[2]->GetAttackComponent()->AssignTarget(P1[2]);
			P2[3]->GetAttackComponent()->AssignTarget(P1[3]);
		}


		// Output the unit information to the test console
		void OutputUnitInfo( GameState &gs )
		{
			// Do this for each UM (one for each player)
			for (std::list<UnitMgr *>::iterator it = gs.UMList.begin(); it != gs.UMList.end(); ++it)
			{
				for (auto &unit : (*it)->unitList)
				{
					std::string message = "ID: " + to_string(unit->id) + 
						"	X: " + to_string(unit->x) + 
						"	Y: " + to_string(unit->y) +
						" Health: " + to_string(unit->GetHealthComponent()->CurrentHealth());
					const char * c_msg = message.c_str();
					Logger::WriteMessage(c_msg);
				}
			}
		}


		void DoSomethingWithUnits( GameState &gs )
		{
			Logger::WriteMessage("Starting Unit Info:");
			OutputUnitInfo(gs);
			
			for (int nTick = 0; nTick < 10; nTick++)
			{
				// Go through each UM for each player...
				for (std::list<UnitMgr *>::iterator it = gs.UMList.begin(); it != gs.UMList.end(); ++it)
				{
					for (auto &unit : (*it)->unitList)
					{
						unit->Update(gs, nTick); // This should perform attacks between enemy units in range
					}
				}
				Logger::WriteMessage("Unit Info after Tick: " + nTick);
				OutputUnitInfo(gs);
			}
		}

		TEST_METHOD(TestUnitCreation)
		{
			UnitMgr UM_Player1;
			UnitMgr UM_Player2;

			PopulateUnits(UM_Player1, UM_Player2);

			GameState gs;

			gs.UMList.push_back(&UM_Player1);
			gs.UMList.push_back(&UM_Player2);

			DoSomethingWithUnits( gs );
		}

	}; // TEST Class "UnitAndComponentTest"
} // UnitTestProject namespace