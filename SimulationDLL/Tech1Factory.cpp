#include "Tech1Factory.h"



Tech1Factory::Tech1Factory()
{
}


Tech1Factory::~Tech1Factory()
{
}

UnitBase * Tech1Factory::CreateUnit(UnitType nType)
{
	return nullptr;

	/*  FROM TEST CLASSES
	UnitBase * ConstructUnit(double x, double y, unsigned int damage, double range, unsigned int cooldown, unsigned int health)
	{
		shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic(damage, range, cooldown));
		shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic(health));
		return(new UnitBase(x, y, nullptr, acptr, hcptr));
	}
	*/

}
