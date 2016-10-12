#pragma once
#include "IUnitFactory.h"


class Tech1Factory :
	public IUnitFactory
{
public:
	Tech1Factory();
	virtual ~Tech1Factory();
	virtual UnitBase * CreateUnit(UnitType nType);
};

