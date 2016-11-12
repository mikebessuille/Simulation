#include "stdafx.h"
#include "Unit.h"
#include "PlayerUnit.h"
#include "VectorUtils.h"

// size, colour, points
const UnitDefaults const Unit::defaults{	30.f, // default_size
											{0, 0, 250}, // blue 
											5, // default_points 
											0 // default_damage
										};

// Constructor for generic shapes that are already pre-created.
Unit::Unit( sf::Shape* ps, sf::Vector2f vel ) : pshape(ps), velocity( vel ), pdefaults( &Unit::defaults )
{
}


// This constructor knows how to create subclass objects using the derived defaults, even though this base
// class constructor happens first. That's because the factory passes in the pointer to the default structure.
// Otherwise, each derived constructor would have to duplicate the basic construction of the object, because
// this base constructor would have no access to the derived defaults.
Unit::Unit(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef ) : velocity( vel ), pdefaults( pdef )
{
	if (pdef == nullptr)
		pdefaults = &Unit::defaults;

	pshape = new sf::CircleShape( pdefaults->default_size );
	pshape->setFillColor(pdefaults->default_colour);
	pshape->setPosition(pos);
	pshape->setOrigin( pdefaults->default_size, pdefaults->default_size); // The center of the object rather than the top-left.
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
	if (player.isShield())
	{
		// do nothing
	}
	else
	{
		// Player eats the unit and gains points.
		player.gainHealth( pdefaults->default_points );
		return(true);
	}
	return(false);
}


void Unit::Bounce(PlayerUnit & player)
{
	// bounce off the player; keep the same speed, just change direction
	sf::Vector2f pu = pshape->getPosition();
	sf::Vector2f pp = player.getPos();
	sf::Vector2f vu = getVelocity();
	float speed = VectorLength(vu); // speed before the collision
	sf::Vector2f vc = pu - pp; // collision vector
	VectorNormalize(vc);

	/* OLD; worked, but not great collision
	setVelocity( vc * speed );
	*/

	sf::Vector2f vp = player.getVelocity(); // get Player's most recent velocity
	float au = VectorDotProduct(vu, vc);
	float ap = VectorDotProduct(vp, vc);
	setVelocity(vu + ((ap - au)*vc));
	// We need to double the change in velocity of the unit, because the collision doesn't
	// impart any change in velocity to the player.
	// setVelocity(vu + (2.f * ( ap-au ) * vc));  // This is too fast!
	setVelocity(vu + (1.5f * (ap - au) * vc)); // Still not great; sometimes the units seem to "stick" to the player for a couple seconds.
}