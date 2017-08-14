#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnitMgr.h"
#include "UnitBase.h"
#include "MoveComponent.h"
#include "GroundAttackComponentBasic.h"
#include "HealthComponentBasic.h"
#include "GameState.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{
	TEST_CLASS(UnitAndComponentTest)
	{
		// This test method acts like a factory
		shared_ptr<UnitBase> ConstructUnit(double x, double y, unsigned int damage, double range, unsigned int cooldown, unsigned int health )
		{
			shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic( damage, range, cooldown ));
			shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic( health ));
			return(make_shared<UnitBase>(x, y, nullptr, acptr, hcptr));
		}


		void PopulateUnits1(UnitMgr &UM1, UnitMgr &UM2)
		{
			// Create some units for Player 1
			shared_ptr<UnitBase> P1[5];
			// x, y, damage, range, cooldown, health
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
			shared_ptr<UnitBase> P2[5];
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
				std::string message = "Unit Info after Tick: " + nTick;
				const char * c_msg = message.c_str();
				Logger::WriteMessage(c_msg);
				OutputUnitInfo(gs);
			}
		}

		TEST_METHOD(TestUnitCreation)
		{
			UnitMgr UM_Player1;
			UnitMgr UM_Player2;

			PopulateUnits1(UM_Player1, UM_Player2);

			GameState gs;

			gs.UMList.push_back(&UM_Player1);
			gs.UMList.push_back(&UM_Player2);

			DoSomethingWithUnits( gs );
		}


		void PopulateUnitsRangeAttack(UnitMgr &UM1, UnitMgr &UM2)
		{
			// Create some units for Player 1
			shared_ptr<UnitBase> P1[2];
			// x, y, damage, range, cooldown, health
			P1[0] = ConstructUnit(0, 0, 5, 16, 2, 12);
			P1[1] = ConstructUnit(0, 1, 5, 10, 2, 8);

			for (int i = 0; i < 2; ++i)
			{
				UM1.AddUnit(P1[i]);
			}

			// Create some units for Player 2
			shared_ptr<UnitBase> P2[2];
			P2[0] = ConstructUnit(10, 10, 5, 10.0, 2, 17);
			P2[1] = ConstructUnit(20, 3, 1, 23, 0, 12);

			for (int i = 0; i < 2; ++i)
			{
				UM2.AddUnit(P2[i]);
			}

			// Then assign them targets, so that they shoot at each other.
			P1[0]->GetAttackComponent()->AssignTarget(P2[0]); // should be in range
			P1[1]->GetAttackComponent()->AssignTarget(P2[1]); // not in range

			P2[0]->GetAttackComponent()->AssignTarget(P1[0]); // not in range
			P2[1]->GetAttackComponent()->AssignTarget(P1[1]); // in range
		} 

		// utility function...
		bool CheckIfUnitIsAlive(std::list<shared_ptr<UnitBase>>::iterator it, std::list<shared_ptr<UnitBase>>::iterator end )
		{
			if (it != end)
			{
				if (*it)
					return( (*it)->GetHealthComponent()->IsAlive() );
				else
				{
					Assert::Fail();
					return false;
				}
			}
			else
			{
				Assert::Fail();  // Not expecting end of list.
				return false;
			}
		}

		TEST_METHOD(TestUnitRangeAttack)
		{
			UnitMgr UM_Player1;
			UnitMgr UM_Player2;

			PopulateUnitsRangeAttack(UM_Player1, UM_Player2);

			GameState gs;

			gs.UMList.push_back(&UM_Player1);
			gs.UMList.push_back(&UM_Player2);

			DoSomethingWithUnits(gs);

			std::list<shared_ptr<UnitBase>>::iterator it = UM_Player1.unitList.begin();
			std::list<shared_ptr<UnitBase>>::iterator end = UM_Player1.unitList.end();
			Assert::IsTrue(CheckIfUnitIsAlive(it, end));
			if( it != end ) ++it;
			Assert::IsFalse(CheckIfUnitIsAlive(it, end )); //P1[1] should be dead

			it = UM_Player2.unitList.begin();
			end = UM_Player2.unitList.end();
			Assert::IsFalse(CheckIfUnitIsAlive(it, end)); // P2[0] should be dead
			if (it != end) ++it;
			Assert::IsTrue(CheckIfUnitIsAlive(it, end));
		}

		// TODO:  Create unit test for new Tech1Factory class

	}; // TEST Class "UnitAndComponentTest"
} // UnitTestProject namespace