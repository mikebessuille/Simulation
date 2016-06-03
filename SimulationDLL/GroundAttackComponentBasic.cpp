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


// If it attacks, this basic component always hits, and always does the same amount of damage.
