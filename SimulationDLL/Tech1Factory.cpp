#include "Tech1Factory.h"
#include "GroundAttackComponentBasic.h"
#include "HealthComponentBasic.h"
#include "MoveComponentGroundBasic.h"
#include "MoveComponentAirBasic.h"
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
		const unsigned int damage(2);
		const double range(12.0);
		const unsigned int cooldown(2); // Fires once per 2 ticks?  (or is it 3?)
		shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic(damage, range, cooldown));

		const unsigned int health(10);
		shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic(health));

		const double maxSpeed(10.0);
	// TODO: REMove this; create a new method on the movecomponent to set the speed.
	// Future movecomponents won't have speed set at creation; they will have a
	// target location, and will adjust speed accordingly.
		const double dx(0.0);
		const double dy(0.0);
		shared_ptr<MoveComponentAirBasic> mcptr(new MoveComponentAirBasic(maxSpeed, dx, dy));

		pUnit = new UnitBase(x, y, mcptr, acptr, hcptr);
	}
	else if (nType == UnitType::TANK)
	{
		const unsigned int damage(3);
		const double range(10.0);
		const unsigned int cooldown(1);
		shared_ptr<GroundAttackComponentBasic> acptr(new GroundAttackComponentBasic(damage, range, cooldown));

		const unsigned int health(20);
		shared_ptr<HealthComponentBasic> hcptr(new HealthComponentBasic(health));

		const double maxSpeed(5.0);
		const double dx(2.0);
		const double dy(2.0);
		shared_ptr<MoveComponentGroundBasic> mcptr(new MoveComponentGroundBasic(maxSpeed, dx, dy));

		pUnit = new UnitBase(x, y, mcptr, acptr, hcptr);
	}
	return pUnit;
}
