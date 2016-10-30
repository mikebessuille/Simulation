#include "stdafx.h" // must be the first line, when using pre-compiled headers
#include <SFML/Graphics.hpp>
#include "main.h"

// using namespace sf;

// This main is never called; winmain in sfmlgame.cpp overrides it somehow.
int main()
{
	return(mainSFML());
}

int mainSFML()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}