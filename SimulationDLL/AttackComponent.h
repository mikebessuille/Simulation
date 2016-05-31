#pragma once
#include "UnitComponent.h"
#include "GameState.h"

// Interface for attack components.  Must implement this interface for each method of attack.
class AttackComponent :  public UnitComponent
{
public:
	AttackComponent( unsigned int maxDamage ) : m_Damage(maxDamage) {}
	virtual ~AttackComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0; // keep this here to make this an interface class

protected:
	unsigned int m_Damage;	// max damage
};

