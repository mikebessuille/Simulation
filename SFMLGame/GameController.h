#pragma once

#include <SFML/Graphics.hpp>
#include "ShapeList.h"
#include "PlayerUnit.h"
#include "TankWidget.h"

class GameController
{
public:
	GameController();
	~GameController();
	void GameLoop(); // The main game loop.

private:
	void HandleEvents();
	void mouseHandler(sf::Event event);
	void UpdateEverything(); // Move all units, player, collisions...
	void Render(); // Render everything in the game
	void RenderStats();
	void RenderUI();

private:
	sf::Vector2i startPos; // for mouse operations
	bool bLeftMouseDown{ false };
	const sf::Time tick{ sf::milliseconds(10) };  // 10ms = 100 frames per second
	ShapeList shapes;
	PlayerUnit player;
	shared_ptr<sf::RenderWindow> pwindow;
	sf::Time elapsed{ sf::milliseconds(0) };

	// For Stats
	sf::Font font;
	sf::Text text;

	// For UI; this could be moved to a UI class that contains all the various screen widgets.
	TankWidget powerDisplay{ sf::Vector2f(25.f, 180.f), 15.f, 100.f };
};

