#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class Renderer; // forward declare

using namespace std;

class Map
{
	friend class Renderer;

public:
	Map();
	~Map();
	void Initialize();
	void TestDraw();
	shared_ptr<sf::RenderWindow> GetWindow() { return(pwindow); };

protected:

private:
	shared_ptr<sf::RenderWindow> pwindow;
	sf::Font font;
	sf::Text text;
};

