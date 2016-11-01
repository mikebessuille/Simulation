#include "stdafx.h"
#include "PlayerUnit.h"

const float PlayerUnit::baseSpeed{ 0.8f };

PlayerUnit::PlayerUnit()
{
	ps = make_shared<sf::CircleShape>(sf::CircleShape(25.f));
	ps->setFillColor(sf::Color::White);
	ps->setPosition(100.f, 100.f);
	ps->setOrigin(25.f, 25.f); // The center of the object rather than the top-left.
}


PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::render(shared_ptr<sf::RenderWindow> pwin )
{
	if( ps != nullptr )
		pwin->draw( *ps );
}


// Utility functions... put these in a new header file or class? (pass by reference or we'll end up changing a copy!)
static float VectorLength(sf::Vector2f &vec)
{
	// Take care of case where length is 0; don't want to normalize it to be huge!
	if (vec.x == 0.f)
		return(vec.y); // this also covers the case where they're both 0
	if (vec.y == 0.f)
		return(vec.x);
	return(sqrt((vec.x * vec.x) + (vec.y * vec.y)));
}

static void VectorNormalize(sf::Vector2f &vec)
{
	float magnitude = VectorLength(vec);
	if (magnitude > 0.f)
		vec /= magnitude;
	if (vec.x > 1.f)
		vec.x = 1.f;
	else if (vec.x < -1.f)
		vec.x = -1.f;
	if (vec.y > 1.f)
		vec.y = 1.f;
	else if (vec.y < -1.f)
		vec.y = -1.f;
}


// Don't rely on events for key handling; poll the keys in the main loop, so that it doesn't stutter (events are less frequent).
void PlayerUnit::move(shared_ptr<sf::RenderWindow> pwin, float speedFactor )
{
	float speed = baseSpeed * speedFactor;
	sf::Vector2f vel{ 0.f, 0.f };
	sf::Vector2f pos = ps->getPosition();
	sf::FloatRect sz = ps->getGlobalBounds();
	sf::Vector2u wsize = pwin->getSize();

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		// Shift key is pressed; go twice as fast.
		speed *= 2.0f;
	}

	// Keyboard
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		vel.y -= 1.0f; // UP
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		vel.y += 1.0f; // Down
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left ))
	{
		vel.x -= 1.0f; // Left
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right ))
	{
		vel.x += 1.0f; // Right
	}

	// Mouse
	if( vel.x == 0.f && vel.y == 0.f )
	{
		// Keyboard didn't change the speed, so we'll use the mouse instead, as long as its buttons aren't pressed.
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition( *pwin ); // Can this be outside the bounds of the current window?  Does that matter?
			sf::Vector2f mousePosF( mousePos ); // convert to float
			vel = mousePosF - pos;
		}
	}

	// Make sure we don't move outside the bounds of the window
	if (((sz.left + sz.width) >= wsize.x) && vel.x > 0.f)
		vel.x = 0.f;
	else if (sz.left <= 0 && vel.x < 0.f)
		vel.x = 0.f;

	if ((sz.top + sz.height) >= wsize.y && vel.y > 0.f)
		vel.y = 0.f;
	else if (sz.top <= 0 && vel.y < 0.f)
		vel.y = 0.f;

	// Normalize vel so you don't move twice as fast when moving diagonally.
	VectorNormalize( vel );
	ps->move( vel * speed );
}

// TODO:  Collision-detection between player and other objects, based on (center + radius) rather than bounding box! 
// (When I create new objects, can I set their position to be based on the center?)
// Avoid O(N^2) collision detection (no need to detect collisions between all objects and each other; just need to
// detect collisions between the player(s) and all other objects, which is O(N) ).


// TODO:  Speed boost?  (Some amount of fuel that gradually fills up, used for speed boost using shift key)
// TODO:  Firing weapons?  (Destroying units...    auto-spawn of new units...)