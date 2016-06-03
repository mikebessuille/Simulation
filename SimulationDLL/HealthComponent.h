#pragma once
#include "UnitComponent.h"

class UnitComponent;
class GameState;

// Interface for health components (components of units that can take damage).  Must implement this interface for each different way that a unit
// can take damage.
class HealthComponent :  public UnitComponent
{
public:
	HealthComponent( unsigned int maxHealth ) : 
		m_MaxHealth(maxHealth),
		m_CurrentHealth(maxHealth) {}
	virtual ~HealthComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0; // keep this here to make this an interface class
	virtual bool TakeDamage(unsigned int damage) = 0; // returns true if unit is still alive, false if it's destroyed
	virtual void Heal(unsigned int health) = 0;
	bool IsAlive() { return(m_CurrentHealth > 0); }
	unsigned int CurrentHealth() { return(m_CurrentHealth); }

protected:
	unsigned int m_MaxHealth;	// full health
	unsigned int m_CurrentHealth;
};

