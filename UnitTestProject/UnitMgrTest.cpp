#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnitMgr.h"
#include "MoveComponent.h"
#include "UnitBase.h"
#include "GameState.h"
#include "Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{
	TEST_CLASS(UnitMgrTest)
	{
	public:
		// Declare this special test version of the MoveComponent within the UnitMgrTest class...
		class MoveComponentBasicTest : public MoveComponent
		{
		public:
			MoveComponentBasicTest(double dx_, double dy_) : MoveComponent( 0 ), dx(dx_), dy(dy_) {}

			~MoveComponentBasicTest() {}

			virtual void Update(GameState &gs, unsigned long nTick)
			{	
				// TODO: move this to the Move() method below
				m_parent->x += dx;
				m_parent->y += dy;
			}

			void Move(GameState &gs, Point ptDest)
			{
				// TODO...
			}

			virtual void Render(GameState &gs, Map &map )
			{
				string message = (string) "Render:  X: [" + (string)to_string(m_parent->x) +
					(string) "]	 Y: [" + (string)to_string(m_parent->y) + (string)"]";
				const char * c_msg = message.c_str();
				Logger::WriteMessage(c_msg);
			}

		protected:
			double dx, dy;	// current velocity

		};

		TEST_METHOD(TestUnitMgrBasics)
		{
			UnitMgr UM;

			Assert::AreEqual(UM.NumUnits(), 0);

			// Assert::IsNotNull();
		}
		
		
		void PopulateList(UnitMgr &UM)
		{
			for (int i = 0; i < 10; i++)
			{
				shared_ptr<UnitTestProject::UnitMgrTest::MoveComponentBasicTest> mcptr(new UnitTestProject::UnitMgrTest::MoveComponentBasicTest((double)10 / (double)(i + 1), 1));
				shared_ptr<UnitBase>pUnit( new UnitBase(0, i, mcptr, nullptr, nullptr ));
				UM.AddUnit( pUnit );
				Assert::AreEqual(UM.NumUnits(), i + 1);
			}
			Assert::AreEqual(UM.NumUnits(), 10);
		}

		void DestroyList(UnitMgr &UM)
		{
			auto it = UM.unitList.begin();
			while( it != UM.unitList.end() )
			{
				int nOldSize = UM.NumUnits();
				shared_ptr<UnitBase>pUnit = *it;
				// delete pUnit; no need since we're removing it from the list
				// TODO: should clear its orders though

				/*
				std::list<UnitBase *>::iterator newIt = it;
				UM.unitList.erase(newIt);
				++it;
				*/
				it = UM.unitList.erase(it);
				int nNewSize = UM.NumUnits();
				Assert::AreNotEqual(nOldSize, nNewSize);
			}
			Assert::AreEqual(UM.NumUnits(), 0);
		}


		void OutputLocations(UnitMgr &UM)
		{
			for (auto it : UM.unitList)
			{
				string message = (string) "ID: " + (string)to_string(it->id) +
									(string) "	X: " + (string)to_string(it->x) + 
									(string) "	Y: " + (string)to_string(it->y);
				const char * c_msg = message.c_str();
				Logger::WriteMessage(c_msg);
			}
		}


		void DoSomethingWithList(UnitMgr &UM)
		{
			Logger::WriteMessage("Starting Unit Positions:");
			OutputLocations(UM);

			GameState gs;
			Map map;
			
			for (int nTick = 0; nTick < 10; nTick++)
			{
				for (auto &unit : UM.unitList)
				{
					unit->Update( gs, nTick );
					unit->Render(gs, map);
				}
			}
			
			// After moving all the units, output their locations to the test output console
			Logger::WriteMessage("Ending Unit Positions:");
			OutputLocations(UM);
		}

		TEST_METHOD(TestUnitMgrList)
		{
			UnitMgr UM;
			Assert::AreEqual(UM.NumUnits(), 0);

			PopulateList(UM);
			DoSomethingWithList(UM);
			DestroyList(UM);
		}

	}; // TEST Class "UnitMgrTest"
} // UnitTestProject namespace