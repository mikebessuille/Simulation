#include "stdafx.h"
#include "Unit.h"


Unit::Unit( sf::Shape* ps, sf::Vector2f vel ) : pshape(ps), velocity( vel )
{
}


Unit::~Unit()
{
}

sf::Shape * Unit::getShape()
{
	return pshape;
}

void Unit::move()
{
	if (pshape)
	{
		pshape->move(velocity);
	}
}
