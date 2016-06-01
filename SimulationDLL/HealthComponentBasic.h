#pragma once
#include "HealthComponent.h"
#include "GameState.h"

class HealthComponentBasic :
	public HealthComponent
{
public:
	HealthComponentBasic( unsigned int maxHealth );
	virtual ~HealthComponentBasic();

	virtual void Update(GameState &gs, unsigned long nTick);
	virtual bool TakeDamage(unsigned int damage);
	virtual void Heal(unsigned int health);
};

