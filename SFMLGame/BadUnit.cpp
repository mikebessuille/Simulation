#include "stdafx.h"
#include "BadUnit.h"
#include <SFML\Graphics.hpp>
#include "VectorUtils.h"



const UnitDefaults const BadUnit::defaults{	25.f, // default_size
											{ 255, 0, 0 }, // Red 
											0, // default_points
											25 // default_damage
										};


BadUnit::BadUnit(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef ) : Unit( pos, vel, pdef )
{
	// Base ctor is called first, so shape is already created.  The factory is responsible for passing in the
	// pointer to the correct defaults structure (for this derived class) so that the base class ctor can correctly
	// construct the derived class using the derived's defaults.
}


// Returns true if the current unit should be destroyed.
bool BadUnit::HandleCollision(PlayerUnit & player)
{
	if (player.isShield())
	{
		Bounce( player );
	}
	else
	{
		// damage the player
		player.damage( pdefaults->default_damage );
		return(true);
	}
	return(false);
}

