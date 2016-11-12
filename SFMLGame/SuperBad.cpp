#include "stdafx.h"
#include "SuperBad.h"


const float SuperBad::default_size{ 15.f };
const sf::Color SuperBad::default_colour(100, 100, 20);
const unsigned int SuperBad::default_damage{ 35 };


SuperBad::SuperBad(sf::Vector2f pos, sf::Vector2f vel) : BadUnit(pos, vel)
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
// Need a copy of this method in SuperBad, even though it's identical to the BadUnit version of the method,
// because the default_damage value is different and we want to ensure we use the copy in this static.
// Perhaps we could create a static structure and *point* to it in each object, rather than rely on statics?
bool SuperBad::HandleCollision(PlayerUnit & player)
{
	if (player.isShield())
	{
		Bounce(player);
	}
	else
	{
		// damage the player
		player.damage(default_damage);
		return(true);
	}
	return(false);
}