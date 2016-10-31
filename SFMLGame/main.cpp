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


int mainSFML()
{
	shared_ptr<sf::RenderWindow> pwindow(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Charlie")); // width, height
	ShapeList shapes;

	while (pwindow->isOpen())
	{
		sf::Event event;
		while (pwindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				pwindow->close();
		}

		shapes.updatePositions(pwindow);
		shapes.render( pwindow );
	}

	return 0;
}

