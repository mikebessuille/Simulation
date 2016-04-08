#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnitMgr.h"
#include "UnitBase.h"
#include "ExampleUnit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
		
		
		void PopulateList(UnitMgr UM)
		{
			for (int i = 0; i < 10; i++)
			{
				UM.AddUnit(new ExampleUnit());
				Assert::AreEqual(UM.NumUnits(), i + 1);
			}
		}

		void DestroyList(UnitMgr UM)
		{
			/*
			// This is a terrible way to destroy the list... and it leaks the actual objects!
			// (It's a list of pointers; this just removes the pointers but doesn't free what is being pointed to)
			auto it = UM.unitList.begin();
			while (it != UM.unitList.end())
			{
				int nOldSize = UM.NumUnits();
				it = UM.unitList.erase(it);
				int nNewSize = UM.NumUnits();
				Assert::AreNotEqual(nOldSize, nNewSize);
				// How can we verify that the memory actually got deleted?
			}
			*/

			for (auto unit : UM.unitList)
			{
				int nOldSize = UM.NumUnits();
				// TODO:  Not sure why this fails to compile!
				delete (UnitBase)*unit;	// Delete the unit that is pointed to
				unit = UM.unitList.erase(unit);	// Remove it from the Vector
				int nNewSize = UM.NumUnits();
				Assert::AreNotEqual(nOldSize, nNewSize);
			}
		}

		void DoSomethingWithList(UnitMgr UM)
		{
			for (auto &unit : UM.unitList)
			{
				//unit->...();
			}
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


/* // This doesn't work... exception in Vector class.
for (int pos = UM.NumUnits(); pos > 0; pos-- )
{
int nOldSize = UM.NumUnits();
UnitBase *pUnit = UM.unitList.at(pos);
UM.DestroyUnit(pos, pUnit );

}
*/