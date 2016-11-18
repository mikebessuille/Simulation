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

void PlayerUnit::Render(shared_ptr<sf::RenderWindow> pwin )
{
	if( ps != nullptr )
		pwin->draw( *ps );

	RenderBullets(pwin);
}


void PlayerUnit::Update(shared_ptr<sf::RenderWindow> pwin, float speedFactor )
{
	Move(pwin, speedFactor);
	UpdateShield();
	UpdateFiring();
	MoveBullets( pwin, speedFactor );
}


// Don't rely on events for key handling; poll key status here, so that it doesn't stutter (events are less frequent).
void PlayerUnit::Move(shared_ptr<sf::RenderWindow> pwin, float speedFactor)
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
	velCurrent = vel * speed;
	ps->move(velCurrent);
}


// Damages the player; returns true if the player loses all his health.
bool PlayerUnit::damage(const unsigned int dmg)
{
	badCollisions++;
	if (dmg > health)
	{
		health = 0;
	}
	else
	{
		health -= dmg;
	}
	return( isAlive() );
}

void PlayerUnit::gainHealth(const unsigned int points)
{
	eaten++;
	health += points;
}


void PlayerUnit::UpdateShield()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
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


void PlayerUnit::UpdateFiring()
{
	// Decide if the user is firing, and if it's ready to fire again (don't fire on every frame!)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isShield())
	{
		sf::Time timeSinceLastShot = lastShotClock.getElapsedTime(); // since the clock was last restarted
		if (timeSinceLastShot > shotCooldownTime)
		{
			timeSinceLastShot = sf::milliseconds(0);
			lastShotClock.restart();

			Fire();
		}
	}
}


// Add a new bullet to the bullet list.
void PlayerUnit::Fire()
{
	Bullet bullet;
	bullet.pos = ps->getPosition();
	bullet.vel = velCurrent;
	VectorNormalize(bullet.vel);
	if (VectorLength(bullet.vel) != 0.f) // Don't fire if the bullet will end up sitting there...
	{ 
		bullet.vel *= bulletSpeed;
		bullet.ticksRemaining = maxBulletTicks;
		m_bullets.push_back(bullet);
	}
}

// Bullets decay after a certain period or if they move outside the window.
void PlayerUnit::MoveBullets( shared_ptr<sf::RenderWindow> pwin, float speedFactor )
{
	sf::Vector2u wsize = pwin->getSize();

	for (auto it = m_bullets.begin(); it != m_bullets.end(); /* do not increment in the loop */)
	{
		(*it).pos += (*it).vel;
		if ((*it).pos.x < 0 || (*it).pos.x >= wsize.x || (*it).pos.y < 0 || (*it).pos.y >= wsize.y)
		{
			it = m_bullets.erase(it);
		}
		else
		{
			(*it).ticksRemaining--;
			if ((*it).ticksRemaining == 0)
			{
				it = m_bullets.erase(it);
			}
			else
			{
				++it; // increment the iterator only if we didn't remove the bullet from the list.
			}
		}
	}
}


// Returns true if a bullet hits a unit at that position & radius.
bool PlayerUnit::CheckBulletHit(sf::Vector2f pos, float radius)
{
	for (auto it = m_bullets.begin(); it != m_bullets.end(); /* do not increment in the loop */)
	{
		// Really should compute with squares and not take the square root; it's expensive.
		if (VectorLength((*it).pos, pos) < radius)
		{
			// Delete the bullet from the list, and stop checking other bullets
			it = m_bullets.erase(it);
			return(true);
		}
		else
		{
			++it;
		}
	}
	return(false);
}


void PlayerUnit::RenderBullets(shared_ptr<sf::RenderWindow> pwin)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(4, 4));
	rect.setOutlineColor(sf::Color::White);

	for (auto bullet : m_bullets)
	{
		rect.setPosition( bullet.pos );
		pwin->draw(rect);
	}
}

// TODO:  Speed boost?  (Some amount of fuel that gradually fills up, used for speed boost using shift key)
// TODO:  (Same thing for shield - can only use it for a few seconds before it needs to recharge).
// TODO:  Show health, shield charge, speed boost as rectangles with text overlay.  Maybe create a generic "bar" UI control class
//		which each of those stats uses?  And a "stats" class that owns all of them?  Instead of the GameController?
