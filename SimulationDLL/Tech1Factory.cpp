#include "Tech1Factory.h"
#include "GroundAttackComponentBasic.h"
#include "HealthComponentBasic.h"
#include "UnitBase.h"
#include <memory>

using namespace std;

Tech1Factory::Tech1Factory()
{
}


Tech1Factory::~Tech1Factory()
{
}

// TODO:  The stats (range, etc) should be read from a file that defines this unit as much as possible
// (Is there a way to identify which Attack/Move/Health components to instantiate, as well?
UnitBase * Tech1Factory::CreateUnit(UnitType nType, double x, double y)
{
	UnitBase *pUnit = nullptr;
	if (nType == UnitType::FIGHTER)
	{
		const unsigned int damage = 3;
		const double range = 10.0;
		const unsigned int cooldown = 1;
		const unsigned int health = 20;
		shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic(damage, range, cooldown));
		shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic(health));
		// TODO:  Create a movecomponent class, and instantiate it here.
		pUnit = new UnitBase(x, y, nullptr, acptr, hcptr);
	}
	else if (nType == UnitType::TANK)
	{

	}
	return pUnit;

	/*  FROM TEST CLASSES
	UnitBase * ConstructUnit(double x, double y, unsigned int damage, double range, unsigned int cooldown, unsigned int health)
	{
		
	}
	*/

}
