#pragma once

#include "GameState.h"
#include <memory>
#include "MoveComponent.h"
//#include "AttackComponent.h"
//#include "HealthComponent.h"

class GameState;
class MoveComponent;

using namespace std;

class UnitBase
{
public:
	UnitBase(	double x_, double y_,
				shared_ptr<MoveComponent> mc_ptr );
	virtual ~UnitBase();
	void Update( GameState &gs, unsigned long nTick );

// Member Variables
private:
	unsigned long nLastUpdateTick;

public:
	double x, y;	// current location; should change this to some kind of "point" structure/object

private:
	// The components that give this unit its real capabilities
	shared_ptr<MoveComponent> m_pMoveComponent;
	//AttackComponent *m_pAttackComponent;
	//DamageComponent *m_pHealthComponent;
	// ... and other pointers for specializations like Harvest, Build, etc.
	// Could convert this to std::vector<UnitComponent *> m_components;

	//TODO:  Need destination location (or could be a list of locations to move in succession; could be a list of patrol points)
	//TODO:  Need a pointer (or identifier) of an enemy target
	//TODO:	 Current damage amount
	//TODO:  Pointer to the current map tile
	//TODO:  Something to identify it's current orders (Move, defend, attack, patrol...)

// Statics
public:
	static unsigned long FrameSize; // milliseconds per tick.   This is a terrible design as this breaks encapsulation.
									// This information really should not be owned by this class!
};

