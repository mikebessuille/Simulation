#include "stdafx.h"
#include "PlayerUnit.h"
#include "VectorUtils.h"


PlayerUnit::PlayerUnit()
{
	ps = make_shared<sf::CircleShape>(sf::CircleShape( radius ));
	ps->setFillColor(sf::Color::White);
	ps->setPosition(100.f, 100.f);
	ps->setOrigin( radius, radius ); // The center of the object rather than the top-left.
}


PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::render(shared_ptr<sf::RenderWindow> pwin )
{
	if( ps != nullptr )
		pwin->draw( *ps );
}


// Don't rely on events for key handling; poll the keys in the main loop, so that it doesn't stutter (events are less frequent).
void PlayerUnit::move(shared_ptr<sf::RenderWindow> pwin, float speedFactor)
{
	float speed = baseSpeed * speedFactor;
	sf::Vector2f vel{ 0.f, 0.f };
	sf::Vector2f pos = ps->getPosition();
	sf::FloatRect sz = ps->getGlobalBounds();
	sf::Vector2u wsize = pwin->getSize();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		// Shift key is pressed; go twice as fast.
		speed *= 2.0f;
	}

	// Keyboard
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		vel.y -= 1.0f; // UP
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		vel.y += 1.0f; // Down
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		vel.x -= 1.0f; // Left
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		vel.x += 1.0f; // Right
	}

	// Mouse
	if (vel.x == 0.f && vel.y == 0.f)
	{
		// Keyboard didn't change the speed, so we'll use the mouse instead, as long as its buttons aren't pressed.
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*pwin); // Can this be outside the bounds of the current window?  Does that matter?
			sf::Vector2f mousePosF(mousePos); // convert to float
			vel = mousePosF - pos;
			// Avoid shaking; don't move at all if the velocity is very small.
			const float t{ 0.1f }; // threshold
			if (vel.x > -t && vel.x < t && vel.y > -t && vel.y < t )
			{
				vel.x = 0.f;
				vel.y = 0.f;
			}
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
	VectorNormalize(vel);
	ps->move(vel * speed);

	// Update other player attributes like shield
	update();
}


// Damages the player; returns true if the player loses all his health.
bool PlayerUnit::damage(const unsigned int dmg)
{
	if (dmg > health)
	{
		health = 0;
	}
	health -= dmg; 
	return( isAlive() );
}

void PlayerUnit::gainHealth(const unsigned int health)
{
}

// Update other attributes like Shield
void PlayerUnit::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// Space bar is pressed; shield is on
		if( bShield == false )
		{
			bShield = true;
			ps->setOutlineThickness( shieldSize );
			ps->setOutlineColor(sf::Color(220, 220, 220));
		}
	}
	else
	{
		if (bShield == true)
		{
			// reset shield to false
			bShield = false;
			ps->setOutlineThickness(0.f);
		}
	}
}


// TODO:  Speed boost?  (Some amount of fuel that gradually fills up, used for speed boost using shift key)
// TODO:  Firing weapons?  (Destroying units...    auto-spawn of new units...)