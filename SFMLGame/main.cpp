#include "stdafx.h" // must be the first line, when using pre-compiled headers
#include <SFML/Graphics.hpp>

#include "main.h"
#include "ShapeList.h"
#include "PlayerUnit.h"

// using namespace sf;

// This main is never called; winmain in sfmlgame.cpp overrides it somehow.
int main()
{
	return(mainSFML());
}

void mouseHandler(sf::Event event, ShapeList &shapes);


// This is the main game loop
int mainSFML()
{
	sf::Clock clock; // starts the clock.
	sf::Time elapsed{ sf::milliseconds(0) };
	const sf::Time tick{ sf::milliseconds(10) };  // 10ms = 100 frames per second
	shared_ptr<sf::RenderWindow> pwindow(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Charlie")); // width, height
	ShapeList shapes;
	PlayerUnit player;

	while (pwindow->isOpen())
	{
		sf::Event event;
		while (pwindow->pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size
				pwindow->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
			}
			else if ( event.type == sf::Event::MouseButtonPressed || 
					  event.type == sf::Event::MouseButtonReleased ||
					  event.type == sf::Event::MouseMoved )
			{
				mouseHandler(event, shapes);
			}
			else if (event.type == sf::Event::Closed)
				pwindow->close();
		}

		
		elapsed = clock.getElapsedTime(); // since the clock was last restarted
		if (elapsed > tick) // So that we don't use 100% CPU and redraw the screen too often.
		{
			if (player.isAlive())
			{
				const float speedFactor = (float)(elapsed / tick);
				shapes.updatePositions(pwindow, speedFactor); // Update position of all units
				player.move(pwindow, speedFactor); // Move the player
				shapes.HandleCollisions(player); // Deal with collisions between player and units
				shapes.SpawnUnits( pwindow );  // Spawn new units gradually...
			}

			// Redraw the screen.  
			pwindow->clear();
			shapes.render(pwindow);
			player.render(pwindow);
			pwindow->display();

			clock.restart();
			elapsed = sf::milliseconds(0);
		}
	}

	return 0;
}


// Currently relies on a global; this should become part of some Mouse Handler class
sf::Vector2i startPos;
bool bLeftMouseDown{ false };

void mouseHandler(sf::Event event, ShapeList &shapes)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			bLeftMouseDown = true;
			startPos.x = event.mouseButton.x;
			startPos.y = event.mouseButton.y;
		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			// On Right-Click remove any Units that are under this mouse position.
			sf::Vector2f pos((float)event.mouseButton.x, (float)event.mouseButton.y);
			shapes.removeUnitsAt(pos);
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && bLeftMouseDown )
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			bLeftMouseDown = false;
			// Create a new shape at the start location, whose velocity depends on the distance the mouse moved.
			sf::CircleShape * ps = new sf::CircleShape(40.f);
			ps->setFillColor(sf::Color::Blue);
			ps->setPosition( (float)event.mouseButton.x, (float)event.mouseButton.y );
			ps->setOrigin(40.f, 40.f); // The center of the object rather than the top-left.
			sf::Vector2f vel( (float)( event.mouseButton.x - startPos.x ) / 100.f,
							  (float)( event.mouseButton.y - startPos.y) / 100.f );
			shared_ptr<Unit> pUnit(new Unit(ps, vel ));
			shapes.AddUnit(pUnit);
		}
	}
}
