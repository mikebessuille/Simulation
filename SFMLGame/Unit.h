#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Unit
{
public:
	Unit(sf::Shape* ps, sf::Vector2f vel);
	virtual ~Unit();
	sf::Shape * getShape();
	void move();
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	sf::Vector2f getVelocity() { return velocity; }

private:
	sf::Shape * pshape{ nullptr };
	sf::Vector2f velocity{ (float)0.0, (float)0.0 };
};

