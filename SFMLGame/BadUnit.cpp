#include "stdafx.h"
#include "BadUnit.h"


const float BadUnit::default_size{ 25.f };
const sf::Color BadUnit::default_colour(255, 0, 0); // Red

BadUnit::BadUnit(sf::Vector2f pos, sf::Vector2f vel) : Unit( pos, vel )
{
	// Base ctor is called first, so shape is already created.
	if (pshape)
	{
		// these use statics defined in this derived class
		pshape->setFillColor(default_colour);
		pshape->setOrigin(default_size, default_size); // The center of the object rather than the top-left.
	}
}


// Returns true if the current unit should be destroyed.
bool BadUnit::HandleCollision(PlayerUnit & player)
{
	return true;
}

