#pragma once
#include "IUnitFactory.h"
#include <memory>

class Tech1Factory :
	public IUnitFactory
{
public:
	Tech1Factory();
	virtual ~Tech1Factory();
	virtual unique_ptr<UnitBase> CreateUnit(UnitType nType, double x, double y);
};

