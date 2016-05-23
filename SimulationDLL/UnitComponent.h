#pragma once

#include "GameState.h"
#include "UnitBase.h"

class GameState;
class UnitBase;

// Abstract base class (Interface)
class UnitComponent
{
public:
	UnitComponent() : m_parent(nullptr) {}
	virtual ~UnitComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0;
	void Attach(UnitBase *pUnit) { m_parent = pUnit; }

protected:
	UnitBase *m_parent;
};

