#pragma once

// Orders can be attack (a unit, a location); move to a location; patrol to a location; ...
// I don't want to have to create / manage / destroy order objects every time a unit is firing at another unit
// An order with a target should only be created because the user selected a target; if the AI decides to fire at its closest enemy,
// no order should be created, because we don't want this unit chasing that target around, potentially.

// If a unit is pointing at an attack target that has already been destroyed, how do we know?  If we mark a unit "destroyed", and if we use
// shared_ptr and remove it from the UM, then it may still be pointed to by other units as a target.  That's okay; the unit would query
// if the target is already destroyed, and if so, remove the target from its target list.  When the last pointer pointing to that
// destroyed target is set to null, the object will get deleted automatically.  Behold, the power of smart pointers.

class Order
{
public:
	Order();
	virtual ~Order();

private: 
};

