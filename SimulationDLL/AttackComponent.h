#pragma once
#include "UnitComponent.h"
// #include "Target.h"

class UnitComponent;
class GameState;
class UnitBase;

// Interface for attack components.  Must implement this interface for each method of attack.
class AttackComponent :  public UnitComponent
{
public:
	AttackComponent(unsigned int maxDamage, double maxRange, unsigned int cooldown);
	virtual ~AttackComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick); // Virtual, but if derived class overrides it, the derived class is responsible for all its work...
	virtual bool ReadyToFire( unsigned long nTick );	// Returns true if the unit's weapon is ready to fire
	virtual UnitBase * GetTarget( GameState &gs );  // Returns a valid target in range, or nullptr if no target is in range
	virtual void Attack(UnitBase *pTarget, unsigned long nTick ); // performs the attack against the target.  Decides whether it hits the target and how much damage it does.

protected:
	unsigned int m_Damage;	// max damage
	double m_Range;			// Max range of this unit
	unsigned int m_CoolDown;	// number of ticks between shots
	unsigned long m_LastTickFired;	// The number of the tick this was last fired.

	// TODO:  AttackComponent needs to have a target unit (or location, or...) to attack.
	// Create a "target" class that can contain a pointer to another unit, or a location, or...?
};



