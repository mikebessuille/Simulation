#pragma once
#include "UnitComponent.h"
// #include "Target.h"
#include <memory>

class UnitComponent;
class GameState;
class Map;
class UnitBase;

// Interface for attack components.  Must implement this interface for each method of attack.
class AttackComponent :  public UnitComponent
{
public:
	AttackComponent(unsigned int maxDamage, double maxRange, unsigned int cooldown);
	virtual ~AttackComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) final; // overriding base component version, but don't want derived classes to override.
	virtual void Render(GameState &gs, Map &map );
	bool AssignTarget(shared_ptr<UnitBase> pTarget); // Returns false if the target is not valid for this unit.  Only set by the player.
	shared_ptr<UnitBase> GetDesignatedTarget(); // Returns null if the unit is not currently targetting anything explicitly (due to player command).

protected:
	bool ReadyToFire(unsigned long nTick);	// Returns true if the unit's weapon is ready to fire
	virtual shared_ptr<UnitBase> GetTarget(GameState &gs);  // Returns a valid target in range, or nullptr if no target is in range
	virtual void Attack(shared_ptr<UnitBase> pTarget, unsigned long nTick); // performs the attack against the target.  Decides whether it hits the target and how much damage it does.
	bool IsValidTarget(shared_ptr<UnitBase> pTarget); // Keep this non-virtual.  Derived classes override IsValidTargetType();
	virtual bool IsValidTargetType(shared_ptr<UnitBase> pTarget) = 0;	// Returns true if the target can be attacked by this unit
	bool IsInRange(shared_ptr<UnitBase> pTarget); // Returns true if the target is in range to be attacked

protected:
	unsigned int	m_Damage;		// max damage
	double			m_Range;		// Max range of this unit
	unsigned int	m_CoolDown;		// number of ticks between shots
	unsigned long	m_LastTickFired;	// The number of the tick this was last fired.

	// Get rid of this - should be encompassed by the attack order class instead.
	shared_ptr<UnitBase>	m_pDesignatedTarget;	// A designated target for this unit.
											// (Unit can still fire on other targets, if the designated target is out of range)
};



