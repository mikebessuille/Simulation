#include "UnitBase.h"
#include "MoveComponent.h"
#include <assert.h>
#include <memory>

// Initialize class statics
unsigned long UnitBase::FrameSize = 0;

using namespace std;

UnitBase::UnitBase( double x_, double y_,
					shared_ptr<MoveComponent> mc_ptr ) : 
	nLastUpdateTick(0),
	x(x_), y(y_),
	m_pMoveComponent( mc_ptr )
{
	if (m_pMoveComponent)
		m_pMoveComponent->Attach(this);
}


UnitBase::~UnitBase()
{
	// for now, the unit "owns" the UnitComponent objects... in future, they should be owned by Systems or
	// UnitComponent Factories...
	// Using shared_ptr<> so the components will be automatically deleted when there are no more references to them.
}


void UnitBase::Update( GameState &gs, unsigned long nTick )
{
	// nLastUpdateTick is not needed, because we must never process more than one tick at a time for each unit,
	// because that would break exact determinism between different machines in the same game.
	// For now, use it as error checking to ensure we update every tick.
	assert(nLastUpdateTick == 0 || nTick == nLastUpdateTick + 1);
	nLastUpdateTick = nTick;

	if (m_pMoveComponent)
		m_pMoveComponent->Update(gs, nTick);
}