#include "Map.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

using namespace std;

Map::Map()
{
	if (font.loadFromFile("AdobeClean-Regular.otf"))
	{
		text.setFont(font);
		text.setCharacterSize(16); // in pixels, not points!
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Regular);
	}
}


Map::~Map()
{
}


void Map::Initialize()
{
	pwindow = make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Simulation Map"); // width, height
}

/*
// The main game loop!
void GameController::GameLoop()
{
	sf::Clock clock; // starts the clock.
	pwindow = make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML Charlie"); // width, height

	while (pwindow->isOpen())
	{
		HandleEvents(); // Mouse, keyboard, user interaction with the window...

		elapsed = clock.getElapsedTime(); // since the clock was last restarted
		if (elapsed > tick) // So that we don't use 100% CPU and redraw the screen too often.
		{
			if (player.isAlive())
			{
				UpdateEverything(); // Move all units, player, handle collisions.
			}

			Render(); // Redraw the screen.  

			clock.restart();
			elapsed = sf::milliseconds(0);
		}
	}
}


void GameController::HandleEvents()
{
	sf::Event event;
	while (pwindow->pollEvent(event))
	{
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size
			pwindow->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
		}
		else if (event.type == sf::Event::MouseButtonPressed ||
			event.type == sf::Event::MouseButtonReleased ||
			event.type == sf::Event::MouseMoved)
		{
			mouseHandler(event);
		}
		else if (event.type == sf::Event::Closed)
			pwindow->close();
	}
}


void GameController::mouseHandler(sf::Event event)
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
	else if (event.type == sf::Event::MouseButtonReleased && bLeftMouseDown)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			bLeftMouseDown = false;
			// Create a new shape at the start location, whose velocity depends on the distance the mouse moved.
			sf::CircleShape * ps = new sf::CircleShape(40.f);
			ps->setFillColor(sf::Color::Blue);
			ps->setPosition((float)event.mouseButton.x, (float)event.mouseButton.y);
			ps->setOrigin(40.f, 40.f); // The center of the object rather than the top-left.
			sf::Vector2f vel((float)(event.mouseButton.x - startPos.x) / 100.f,
				(float)(event.mouseButton.y - startPos.y) / 100.f);
			shared_ptr<Unit> pUnit(new Unit(ps, vel));
			shapes.AddUnit(pUnit);
		}
	}
}

void GameController::UpdateEverything()
{
	const float speedFactor = (float)(elapsed / tick);
	shapes.updatePositions(pwindow, speedFactor); // Update position of all units
	player.Update(pwindow, speedFactor); // Move the player, deal with shield, etc.
	shapes.HandleCollisions(player); // Deal with collisions between player and units
	shapes.SpawnUnits(pwindow);  // Spawn new units gradually...
}


// Render everything
void GameController::Render()
{
	pwindow->clear();
	shapes.render(pwindow);
	player.Render(pwindow);
	RenderStats();
	RenderUI();
	pwindow->display();
}


// Could move this to a separate "Stats" class that is owned by the GameController.
void GameController::RenderStats()
{
	// Should I use a single text object for all the lines? Or one for each line?
	std::stringstream ss;
	text.setString("Stats:");
	text.setPosition(sf::Vector2f(25.f, 50.f));
	pwindow->draw(text);

	ss.str(""); // Clear the string
	ss << "Health: " << player.getHealth();
	text.setString(ss.str());
	text.setPosition(sf::Vector2f(25.f, 70.f));
	pwindow->draw(text);

	ss.str(""); // Clear the string
	ss << "Units Eaten: " << player.getEaten();
	text.setString(ss.str());
	text.setPosition(sf::Vector2f(25.f, 90.f));
	pwindow->draw(text);

	ss.str(""); // Clear the string
	ss << "Units Shot: " << player.getShot();
	text.setString(ss.str());
	text.setPosition(sf::Vector2f(25.f, 110.f));
	pwindow->draw(text);

	ss.str(""); // Clear the string
	ss << "Score: " << player.getScore();
	text.setString(ss.str());
	text.setPosition(sf::Vector2f(25.f, 130.f));
	pwindow->draw(text);

	ss.str(""); // Clear the string
	float fps = sf::milliseconds(1000) / elapsed;
	ss << "Frame Rate: " << (int)fps << " fps.";
	text.setString(ss.str());
	text.setPosition(sf::Vector2f(25.f, 150.f));
	pwindow->draw(text);
}

void GameController::RenderUI()
{
	powerDisplay.Render(pwindow, (player.getPower() * 100) / MaxShieldPower);
}

*/