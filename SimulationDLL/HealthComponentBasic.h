#pragma once
#include "HealthComponent.h"
// #include "GameState.h"   // No; do NOT include Gamestate or we get a circular include problem

class GameState;

class HealthComponentBasic :
	public HealthComponent
{
public:
	HealthComponentBasic( unsigned int maxHealth );
	virtual ~HealthComponentBasic();

	virtual void Update(GameState &gs, unsigned long nTick);
	virtual void Render(GameState &gs);
	virtual bool TakeDamage(unsigned int damage);
	virtual void Heal(unsigned int health);
};

