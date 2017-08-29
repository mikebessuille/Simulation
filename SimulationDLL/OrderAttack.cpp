#include "OrderAttack.h"
#include "AttackComponent.h"



OrderAttack::OrderAttack( shared_ptr<UnitBase> pTarget ) : m_pTarget( pTarget )
{
}


OrderAttack::~OrderAttack()
{
}


// punit is the unit that is executing the order.  The target is already set in m_pTarget
bool OrderAttack::Execute(GameState &gs, UnitBase * punit, unsigned long nTick )
{
	if (punit == nullptr)
	{
		return(false);
	}

	if (m_pTarget == nullptr || m_pTarget->IsAlive() == false)
	{
		// target doesn't exist or id already destroyed, so this order should be removed.
		return(false);
	}

	shared_ptr<AttackComponent> pac = punit->GetAttackComponent();
	if (pac == nullptr)
	{
		// This unit can't attack, so it shouldn't have an attack order.
		return(false);
	}
	
	if (!pac->AssignTarget( m_pTarget ))
	{
		// the target is not a valid target for this unit to attack. Should only do this once, when the order is created, not every Execute() call.
		return(false);
	}

	// TODO:  Currently this just causes the unit to sit there and shoot if in range.  Need to refactor this so that the Order decides whether to move
	// closer to the target if it's not in range.
	pac->Update( gs, nTick );
	// If the target gets destroyed by this attack, this will be detected on the next call to Execute() for this order.  So we can always return true here.
	return(true);	
}
