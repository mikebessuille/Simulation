#include "stdafx.h"
#include "Unit.h"


Unit::Unit( sf::Shape* ps, sf::Vector2f vel ) : pshape(ps), velocity( vel )
{
}


Unit::~Unit()
{
	// The unit "owns" the shape, so must delete it here.
	delete pshape; // This is null-safe; no need to check if it's non-null before deleting.
}

sf::Shape * Unit::getShape()
{
	return pshape;
}

void Unit::move( float speedFactor )
{
	if (pshape)
	{
		pshape->move(velocity * speedFactor );
	}
}
