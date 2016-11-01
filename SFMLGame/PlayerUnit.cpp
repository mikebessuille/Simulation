#include "stdafx.h"
#include "PlayerUnit.h"


PlayerUnit::PlayerUnit()
{
	ps = make_shared<sf::CircleShape>(sf::CircleShape(25.f));
	ps->setFillColor(sf::Color::White);
	ps->setPosition(100.f, 100.f);
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
void PlayerUnit::move(shared_ptr<sf::RenderWindow> pwin )
{
	float speed = 0.5;
	sf::Vector2f vel{ 0.f, 0.f };
	//sf::Vector2f pos = ps->getPosition();
	sf::FloatRect sz = ps->getGlobalBounds();
	sf::Vector2u wsize = pwin->getSize();

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		// Shift key is pressed; go twice as fast.
		speed *= 2.0f;
	}

	if (( sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) && sz.top > 0 )
	{
		vel.y -= speed; // UP
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (sz.top + sz.height) < wsize.y )
	{
		vel.y += speed; // Down
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left )) && sz.left > 0)
	{
		vel.x -= speed; // Left
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right )) && (sz.left + sz.width) < wsize.x )
	{
		vel.x += speed; // Right
	}

	ps->move( vel );
}
