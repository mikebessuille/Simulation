#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

class TankWidget
{
public:
	TankWidget( sf::Vector2f _pos, float _width, float _height );
	virtual ~TankWidget();

	void Render( shared_ptr<sf::RenderWindow> pwindow, unsigned int percent );

private:
	sf::RectangleShape containerShape;
	sf::RectangleShape amountShape;

	sf::Vector2f pos;
	float width;
	float height;
};

