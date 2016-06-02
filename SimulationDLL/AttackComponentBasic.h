#pragma once
#include "AttackComponent.h"

class GameState;

class AttackComponentBasic :
	public AttackComponent
{
public:
	AttackComponentBasic(unsigned int maxDamage, double maxRange );
	virtual ~AttackComponentBasic();
	virtual void Update(GameState &gs, unsigned long nTick);
};

