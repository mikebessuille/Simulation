#include "stdafx.h"
#include "Unit.h"
#include "PlayerUnit.h"


const float Unit::default_size{ 30.f };
const sf::Color Unit::default_colour(0, 0, 250); // Blue

Unit::Unit( sf::Shape* ps, sf::Vector2f vel ) : pshape(ps), velocity( vel )
{
}


Unit::Unit(sf::Vector2f pos, sf::Vector2f vel) : velocity( vel )
{
	// TODO: This doesn't work, because the derived class has not yet been constructed, so
	// the virtual functions def_size() and def_colour() always call the base implementation.

	//float sz = def_size();
	pshape = new sf::CircleShape( default_size );
	//pshape->setFillColor( def_colour());
	pshape->setFillColor(default_colour);
	pshape->setPosition(pos);
	//pshape->setOrigin(sz, sz); // The center of the object rather than the top-left.
	pshape->setOrigin(default_size, default_size); // The center of the object rather than the top-left.
}


Unit::~Unit()
{
	// The unit "owns" the shape, so must delete it here.  (The smart pointer in ShapeList will destroy
	// the unit, but not the shape itself!!!
	// We wouldn't have to do this if the Unit contained a shared_ptr to a shape, instead of a raw pointer.
	delete pshape; // This is null-safe; no need to check if it's non-null before deleting.
}

sf::Shape * Unit::getShape()
{
	return pshape;
}

void Unit::move( const float speedFactor )
{
	if (pshape)
	{
		pshape->move(velocity * speedFactor );
	}
}


// Returns true if the current unit should be destroyed.
bool Unit::HandleCollision(PlayerUnit & player)
{
	return false;
}
