#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnitMgr.h"
#include "ExampleUnit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestProject
{		
	TEST_CLASS(UnitMgrTest)
	{
	public:
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
				ExampleUnit *pUnit = new ExampleUnit();
				pUnit->x = 0;
				pUnit->y = i;
				pUnit->dx = (double)10/(i+1);
				pUnit->dy = 0;
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
				UnitBase *pUnit = *it;
				delete pUnit;

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
				std::string message = "X: " + to_string(it->x) + "		Y: " + to_string(it->y);
				const char * c_msg = message.c_str();
				Logger::WriteMessage(c_msg);
			}
		}


		void DoSomethingWithList(UnitMgr &UM)
		{
			Logger::WriteMessage("Starting Unit Positions:");
			OutputLocations(UM);
			
			
			for (int nTick = 0; nTick < 10; nTick++)
			{
				for (auto &unit : UM.unitList)
				{
					unit->x += unit->dx;
					unit->y += unit->dy;
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

	};
}