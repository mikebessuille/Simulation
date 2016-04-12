#include "stdafx.h"
#include "CppUnitTest.h"
#include "UnitMgr.h"
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
			auto it = UM.unitList.begin();
			while( it != UM.unitList.end() )
			{
				int nOldSize = UM.NumUnits();
				UnitBase *pUnit = *it;
				delete pUnit;

				std::list<UnitBase *>::iterator newIt = it;
				UM.unitList.erase(newIt); // ignore it's return iterator
				int nNewSize = UM.NumUnits();
				Assert::AreNotEqual(nOldSize, nNewSize);

				++it;
				// increment at end of while loop.  If i tried to use a for loop, I would get a KW ITER.END.DEREF.MIGHT
				// with:
				// delete pUnit;
				// it = UM.unitList.erase( it ); // returns next iterator
				// because the iterator returned by erase may point to the end.  Then it was being incremented in the for loop
				// (now pointing past the end!)
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