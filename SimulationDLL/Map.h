#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class Renderer; // forward declare

class Map
{
	friend class Renderer;

public:
	Map();
	~Map();
	void Initialize();
	void TestDraw();

protected:

private:
	std::shared_ptr<sf::RenderWindow> pwindow;
	sf::Font font;
	sf::Text text;
};

