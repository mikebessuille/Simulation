#pragma once
#include "UnitComponent.h"

class UnitComponent;
class GameState;

// Interface for attack components.  Must implement this interface for each method of attack.
class AttackComponent :  public UnitComponent
{
public:
	AttackComponent( unsigned int maxDamage, double maxRange ) : 
		m_Damage(maxDamage), m_Range( maxRange) {}
	virtual ~AttackComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0; // keep this here to make this an interface class

protected:
	unsigned int m_Damage;	// max damage
	double m_Range;			// Max range of this unit
	// TODO:  AttackComponent needs to have a target unit (or location, or...) to attack.
	// Create a "target" class that can contain a pointer to another unit, or a location, or...?
};



