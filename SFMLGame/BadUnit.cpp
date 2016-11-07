#include "stdafx.h"
#include "BadUnit.h"
#include <SFML\Graphics.hpp>
#include "VectorUtils.h"


const float BadUnit::default_size{ 25.f };
const sf::Color BadUnit::default_colour(255, 0, 0); // Red
const unsigned int BadUnit::default_damage{ 20 };

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
	if (player.isShield())
	{
		// bounce off the player; keep the same speed, just change direction
		sf::Vector2f pu = pshape->getPosition();
		sf::Vector2f pp = player.getPos();
		sf::Vector2f vu = getVelocity();
		float speed = VectorLength( vu ); // speed before the collision
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
		setVelocity(vu + (1.5f * ( ap-au ) * vc)); // Still not great; sometimes the units seem to "stick" to the player for a couple seconds.
	}
	else
	{
		// damage the player
		player.damage( default_damage );
		return(true);
	}
	return(false);
}

