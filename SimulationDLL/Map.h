#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class Map
{
public:
	Map();
	~Map();
	void Initialize();

private:
	std::shared_ptr<sf::RenderWindow> pwindow;
	sf::Font font;
	sf::Text text;
};

