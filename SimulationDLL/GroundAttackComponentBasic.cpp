#include "GroundAttackComponentBasic.h"
#include "UnitBase.h"



GroundAttackComponentBasic::GroundAttackComponentBasic( unsigned int maxDamage,
														double maxRange, 
														unsigned int cooldown ) : 
	AttackComponent( maxDamage, maxRange, cooldown )
{
}


GroundAttackComponentBasic::~GroundAttackComponentBasic()
{
}


// If it attacks, this basic component always hits, and always does the same amount of damage.


// Returns true if the target can be attacked by this unit
bool GroundAttackComponentBasic::IsValidTargetType(shared_ptr<UnitBase> pTarget)
{
	// TODO:  return true only if the target is a ground unit (or an air unit that is on the ground...)
	return(true);
}
