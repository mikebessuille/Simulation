#pragma once

#include "UnitBase.h"

class UnitBase;

// Abstract base class (Interface)
class UnitFactory
{
public:
	UnitFactory() {}
	virtual ~UnitFactory() {}
	virtual UnitBase * CreateUnit() = 0;
	void Attach(UnitBase *pUnit) { m_parent = pUnit; }
};