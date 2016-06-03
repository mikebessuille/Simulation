#include "AttackComponent.h"
// #include "Target.h"
#include "UnitBase.h"
#include "HealthComponent.h"

AttackComponent::AttackComponent(unsigned int maxDamage, double maxRange, unsigned int cooldown) :
	m_Damage(maxDamage),
	m_Range(maxRange),
	m_CoolDown(cooldown),
	m_LastTickFired(0),
	m_pDesignatedTarget(nullptr)
{
}


// Consider making this method non-virtual
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

	// If this component has a designated target that is in range...
	UnitBase * pDesTarget = GetDesignatedTarget();
	if (pDesTarget && IsInRange(pDesTarget) && IsValidTarget(pDesTarget))
	{
		pTarget = pDesTarget;
	}

	else // if( pTarget == nullptr )
	{
		// find the closest enemy unit in range, and that is attackable (has a health component)
		// TODO:  implement search for enemy units; need to go through all units, to find the closest one.
	}
		
	return(pTarget); // may be null
}


// performs the attack against the target.  Decides whether it hits the target and how much damage it does.
void AttackComponent::Attack(UnitBase *pTarget, unsigned long nTick )
{
	if (pTarget)
	{
		m_LastTickFired = nTick;

		shared_ptr<HealthComponent> pHealth = pTarget->GetHealthComponent();
		if (pHealth)
		{
			pHealth->TakeDamage(m_Damage);
		}
	}
}


// Inherited classes will override IsValidTarget() and provide an implementation based on what kinds of targets this unit can actually attack.
// Ex, Air units?  Attacking an area?  etc.
bool AttackComponent::IsValidTarget(UnitBase *pTarget)
{
	if (pTarget )
	{
		shared_ptr<HealthComponent> pHealth = pTarget->GetHealthComponent();
		if (pHealth && pHealth->IsAlive())
		{
			if (IsValidTargetType(pTarget))
			{
				return(true);
			}
		}
	}
	return(false);
}


// Helper function... put this someplace where it can be re-used
double Distance(double x1, double y1, double x2, double y2)
{
	return(sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}


bool AttackComponent::IsInRange(UnitBase *pTarget)
{
	if (pTarget)
	{
		double d; // snort...
		d = Distance(m_parent->x, m_parent->y, pTarget->x, pTarget->y);
		if( m_Range <= d )
			return(true);
	}
	return(false);
}


// Returns false if the target is not valid for this unit.  Only set by the player.
bool AttackComponent::AssignTarget(UnitBase *pTarget)
{
	if (IsValidTarget(pTarget))
	{
		m_pDesignatedTarget = pTarget;
		return(true);
	}
	else
	{
		// clear the currently designated target if there was one... (is that really what we should do?)
		m_pDesignatedTarget = nullptr;
		return(false);
	}
}


// Returns the unit's currently designated attack target, IF it exists.
// TODO:  May want to remove this and put it into the UnitBase class or into a "target" or "order" component, so we don't have to worry about 
// having multiple conflicting orders at the same time (a movecomponent order to move somewhere, and patrol order, and an attack order).
UnitBase * AttackComponent::GetDesignatedTarget()
{
	return(m_pDesignatedTarget);
}
