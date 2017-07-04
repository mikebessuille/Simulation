#include "UnitBase.h"
#include <assert.h>
#include <memory>

// Moved the following includes to the CPP instead of the header file, to avoid circular includes.
#include "MoveComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"

using namespace std;

// TODO: this global should be moved into whatever factory class is responsible for creating units.
unsigned int UnitBase::LastId = 0;

UnitBase::UnitBase( double x_, double y_,
					shared_ptr<MoveComponent> mc_ptr,
					shared_ptr<AttackComponent> ac_ptr,
					shared_ptr<HealthComponent> hc_ptr ) :
	x(x_), y(y_),
	nLastUpdateTick(0),
	m_pMoveComponent( mc_ptr ),
	m_pAttackComponent( ac_ptr ),
	m_pHealthComponent( hc_ptr )
{
	// This is safe within the constructor, because we aren't using these pointers, just storing them inside the component.
	if (m_pMoveComponent)
		m_pMoveComponent->Attach(this);	
	if (m_pAttackComponent)
		m_pAttackComponent->Attach(this);
	if (m_pHealthComponent)
		m_pHealthComponent->Attach(this);

	SetUnitID( id );
}


UnitBase::~UnitBase()
{
	// for now, the unit "owns" the UnitComponent objects... in future, they should be owned by Systems or
	// UnitComponent Factories...
	// Using shared_ptr<> so the components will be automatically deleted when there are no more references to them.
}


void UnitBase::Update( GameState &gs, const unsigned long nTick )
{
	// nLastUpdateTick is not needed, because we must never process more than one tick at a time for each unit,
	// because that would break exact determinism between different machines in the same game.
	// For now, use it as error checking to ensure we update every tick.
	assert(nLastUpdateTick == 0 || nTick == nLastUpdateTick + 1);
	nLastUpdateTick = nTick;

	if (m_pMoveComponent)
		m_pMoveComponent->Update(gs, nTick);
	if (m_pAttackComponent)
		m_pAttackComponent->Update(gs, nTick);
	if (m_pHealthComponent)
		m_pHealthComponent->Update(gs, nTick);
}


void UnitBase::Render(GameState &gs )
{
	if (m_pMoveComponent)
		m_pMoveComponent->Render( gs );
	if (m_pAttackComponent)
		m_pAttackComponent->Render( gs );
	if (m_pHealthComponent)
		m_pHealthComponent->Render( gs );
}

// Static
void UnitBase::SetUnitID(unsigned int &id_)
{
	LastId++; // TODO: This shouldn't be part of the UnitBase class, but should be part of a Factory class.
	id_ = LastId;
}

// TODO:  Use Composite design pattern so that the base class is an abstraction can represent a single unit, or a group of units.
// That way, other operations can treat the class the same whether it's a single tank or a group (army) of tanks.
// For example, a UI class that gives orders to a Unit should be able to operate on a group and give similar orders to the group without even
// knowing that it's a group.