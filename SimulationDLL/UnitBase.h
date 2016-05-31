#pragma once

#include "GameState.h"
#include <memory>
#include "MoveComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"

class GameState;
class MoveComponent;
class AttackComponent;
class HealthComponent;

using namespace std;

// Constructed mostly from Composition, not Inheritance
class UnitBase
{
public:
	UnitBase(	double x_, double y_,
				shared_ptr<MoveComponent> mc_ptr,
				shared_ptr<AttackComponent> ac_ptr,
				shared_ptr<HealthComponent> hc_ptr );
	virtual ~UnitBase();
	void Update( GameState &gs, const unsigned long nTick );

// Static Functions
protected:
	static void SetUnitID(unsigned int &id_);
	static unsigned int LastId;

// Member Variables
public:
	double x, y;	// current location; should change this to some kind of "point" structure/object
	unsigned int id;	// Unique unit id;  This allows units to be destroyed without leaving dangling pointers
						// (ex, if A targets B but B is subsequently destroyed; yet A still points to B...)
						// Could instead use smart pointers?

protected:
	unsigned long nLastUpdateTick;
	// The components that give this unit its real capabilities
	shared_ptr<MoveComponent> m_pMoveComponent;
	shared_ptr<AttackComponent>  m_pAttackComponent;
	shared_ptr<HealthComponent>  m_pHealthComponent;
	// ... and other pointers for specializations like Harvest, Build, etc.
	// Could convert this to std::vector<UnitComponent *> m_components;

	//TODO:  Pointer to the current map tile
	//TODO:  Something to identify it's current orders (Move, attack, patrol, do nothing...)
	//		 Or is that better just being part of each component?
	//		 What if different components get out of sync and have different, conflicting orders?
};

