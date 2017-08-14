#pragma once

#include <memory>

class GameState;
class UnitBase;
class Map;

using namespace std;

// Abstract base class (Interface)
class UnitComponent
{
public:
	UnitComponent() : m_parent(nullptr) {}
	virtual ~UnitComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0;
	virtual void Render( GameState &gs, Map &map ) = 0;
	void Attach( UnitBase* pUnit) { m_parent = pUnit; } // Keep this as UnitBase*, rather than shared_ptr<UnitBase>

protected:
	UnitBase * m_parent;
};

