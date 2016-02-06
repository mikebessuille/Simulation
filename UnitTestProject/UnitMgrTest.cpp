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

		TEST_METHOD(TestUnitMgrList)
		{
			UnitMgr UM;
			Assert::AreEqual(UM.NumUnits(), 0);

			for (int i = 0; i < 10; i++)
			{
				UM.AddUnit(new ExampleUnit());
				Assert::AreEqual(UM.NumUnits(), i+1);
			}
		
			/* // This doesn't work... exception in Vector class.
			for (int pos = UM.NumUnits(); pos > 0; pos-- )
			{
				int nOldSize = UM.NumUnits();
				UnitBase *pUnit = UM.unitList.at(pos);
				UM.DestroyUnit(pos, pUnit );

			}
			*/


			for (auto &unit : UM.unitList)
			{
				//unit->...();
			}
			
			auto it = UM.unitList.begin();
			while (it != UM.unitList.end())
			{
				int nOldSize = UM.NumUnits();
				it = UM.unitList.erase(it);
				int nNewSize = UM.NumUnits();
				Assert::AreNotEqual(nOldSize, nNewSize);
				// How can we verify that the memory actually got deleted?
			}
		}

	};
}