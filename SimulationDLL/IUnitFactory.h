#pragma once
#include "UnitTypes.h"
#include <memory>

class UnitComponent;
class UnitBase;

// Interface for Unit Factories
class IUnitFactory
{
public:
	IUnitFactory() {};
	virtual ~IUnitFactory() {};
	virtual shared_ptr<UnitBase> CreateUnit( UnitType nType, double x, double y ) = 0; // keep this here to make this an interface class
};


// TODO: Somehow would like each concrete factory to register the types of units it can create.
// Maybe each factory should contain a member that is initialized something like this, as pairs of names and id's, where the i
// is used as the UnitType passed to CreateUnit.
// We'll have different factories for engineer, commander, Tech-1 factory, T2 factory, etc.
// And each will enumerate its own list of units that it can create.
// Those factories may inherit from each other; ex, T2 factory can extend T1 Factory.
// T2 factory may provide a set of special units it can create, but if asked to create a T1 unit, it will
// just call T1 Factory's CreateUnit() method.
// Want this to be extensible through plugins...
// Would love it to be fully extensible where unit definitions are in XML rather than hardcoded in code.