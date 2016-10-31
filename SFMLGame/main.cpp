#include "stdafx.h" // must be the first line, when using pre-compiled headers
#include <SFML/Graphics.hpp>

#include "main.h"
#include "ShapeList.h"

// using namespace sf;

// This main is never called; winmain in sfmlgame.cpp overrides it somehow.
int main()
{
	return(mainSFML());
}

void mouseHandler(sf::Event event, ShapeList &shapes);

int mainSFML()
{
	shared_ptr<sf::RenderWindow> pwindow(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Charlie")); // width, height
	ShapeList shapes;

	while (pwindow->isOpen())
	{
		sf::Event event;
		while (pwindow->pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size
				pwindow->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
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

		shapes.updatePositions(pwindow);
		shapes.render( pwindow );
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
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && bLeftMouseDown )
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			bLeftMouseDown = false;
			// Create a new shape at the start location, whose velocity depends on the distance the mouse moved.
			sf::CircleShape * ps(new sf::CircleShape(40.f));
			ps->setFillColor(sf::Color::Blue);
			ps->setPosition( event.mouseButton.x, event.mouseButton.y );
			sf::Vector2f vel( (float)( event.mouseButton.x - startPos.x ) / 100.f,
							  (float)( event.mouseButton.y - startPos.y) / 100.f );
			shared_ptr<Unit> pUnit(new Unit(ps, vel ));
			shapes.AddUnit(pUnit);
		}
	}
}

