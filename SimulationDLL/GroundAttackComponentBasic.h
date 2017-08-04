#pragma once
#include "AttackComponent.h"

class GameState;

class GroundAttackComponentBasic :
	public AttackComponent
{
public:
	GroundAttackComponentBasic(unsigned int maxDamage, double maxRange, unsigned int cooldown );
	virtual ~GroundAttackComponentBasic();
	virtual bool IsValidTargetType(shared_ptr<UnitBase> pTarget);
};

