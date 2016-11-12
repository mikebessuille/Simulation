#include "stdafx.h"
#include "SuperBad.h"


const UnitDefaults const SuperBad::defaults{	15.f, // default_size
												{ 250, 250, 0 }, // Yellow
												0, // default_points
												35 // default_damage
											};


SuperBad::SuperBad(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef ) : BadUnit(pos, vel, pdef )
{
	// Base ctor is called first, so shape is already created.
}
