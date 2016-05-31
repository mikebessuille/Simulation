#pragma once
#include "UnitComponent.h"
#include "GameState.h"

// Interface for health components (components of units that can take damage).  Must implement this interface for each different way that a unit
// can take damage.
class HealthComponent :  public UnitComponent
{
public:
	HealthComponent( unsigned int maxHealth ) : 
		m_Health(maxHealth),
		m_CurrentHealth(maxHealth) {}
	virtual ~HealthComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0; // keep this here to make this an interface class

protected:
	unsigned int m_Health;	// full health
	unsigned int m_CurrentHealth;
};

