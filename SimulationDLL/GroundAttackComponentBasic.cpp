#include "GroundAttackComponentBasic.h"



GroundAttackComponentBasic::GroundAttackComponentBasic( unsigned int maxDamage,
														double maxRange, 
														unsigned int cooldown ) : 
	AttackComponent( maxDamage, maxRange, cooldown )
{
}


GroundAttackComponentBasic::~GroundAttackComponentBasic()
{
}

void GroundAttackComponentBasic::Update(GameState &gs, unsigned long nTick)
{
	// If it is ready to attack (rate of fire / cooldown)

	// if there's a target in range...
	// (if not... is there another enemy in range to attack while en route to the target?)
	// And if the target is an appropriate type that this unit is able to attack

	// Some of that attack logic (above) should be put into the base class perhaps.  Maybe I can
	// make the whole Update method non-virtual in the base AttackComponent class, and then
	// override methods like GetTarget() which decides whether it can attack a particular type, and
	// Attack() which decides whether it hits the target and how much damage it does.

	// If it attacks, this basic component always hits, and always does the same amount of damage.
}