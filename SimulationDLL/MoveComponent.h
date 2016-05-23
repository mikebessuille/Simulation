#pragma once
#include "UnitComponent.h"
#include "GameState.h"


class MoveComponent :  public UnitComponent
{
public:
	MoveComponent( double dx_, double dy_ );
	virtual ~MoveComponent();
	virtual void Update(GameState &gs, unsigned long nTick);


private:
	double dx, dy;	// current velocity
};

