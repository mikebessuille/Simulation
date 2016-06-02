#include "AttackComponentBasic.h"



AttackComponentBasic::AttackComponentBasic( unsigned int maxDamage, double maxRange ) : 
	AttackComponent( maxDamage, maxRange )
{
}


AttackComponentBasic::~AttackComponentBasic()
{
}

void AttackComponentBasic::Update(GameState &gs, unsigned long nTick)
{
	// Decide whether it's in range to attack
	// If it is, this basic component always hits, and always does the same amount of damage.
	// Todo: also need some kind of fire rate (part of base class?)
}