#include "AttackComponent.h"
// #include "Target.h"
#include "UnitBase.h"

AttackComponent::AttackComponent(unsigned int maxDamage, double maxRange, unsigned int cooldown) :
	m_Damage(maxDamage),
	m_Range(maxRange),
	m_CoolDown(cooldown),
	m_LastTickFired(0)
{
}

void AttackComponent::Update(GameState &gs, unsigned long nTick)
{
	// If it is ready to attack (rate of fire / cooldown)
	if (ReadyToFire( nTick ))
	{
		// if there's a target in range...
		UnitBase *pTarget = GetTarget( gs );
		if (pTarget != nullptr)
		{
			Attack( pTarget, nTick );
		}
	}
}

// Returns true if the unit's weapon is ready to fire
bool AttackComponent::ReadyToFire( unsigned long nTick )
{
	if (nTick >= m_LastTickFired + m_CoolDown)
		return(true);
	else
		return(false);
}


// Returns a valid target in range, or nullptr if no target is in range.
// This is going to be called very often, so we need to make this extremely efficient.
// For example, only go through units on the current (or nearby) map tile.  Only go through enemy units...
UnitBase * AttackComponent::GetTarget( GameState &gs )
{
	UnitBase *pTarget = nullptr;

	// TODO: If this component has a designated target that is in range...
	
	// TODO: else find the closest enemy unit in range, and that is attackable (has a health component)

	// TODO: call a virtual method "IsValidTarget()" so subclasses can choose to only attack certain types of targets (e.g., only ground targets)
	
	return(pTarget); // may be null
}


// performs the attack against the target.  Decides whether it hits the target and how much damage it does.
void AttackComponent::Attack(UnitBase *pTarget, unsigned long nTick )
{
	m_LastTickFired = nTick;

	// TODO: Call the target unit's health component so it takes damage.
}