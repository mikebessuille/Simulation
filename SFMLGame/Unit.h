#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Unit
{
public:
	Unit(sf::Shape* ps, sf::Vector2f vel);
	virtual ~Unit();
	// These don't work with KW yet...
	Unit& operator=(Unit rhs) = delete; // Disallow assignment operator, to prevent leaking of pshape
	Unit(const Unit& other) = delete; // Disallow copy constructor, to prevent leaking of pshape

	sf::Shape * getShape();
	void move( float speedFactor );
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	sf::Vector2f getVelocity() { return velocity; }

private:
	// Make these (copy ctor, assignment operator) private, simply because KW doesn't properly detect the C++11 "delete" functionality and will assume the default
	// copy constructor & assignment operators were created, which leads KW to believe there are memory problems.
	// Unit& operator=(Unit rhs); // Disallow assignment operator, to prevent leaking of pshape
	// Unit(const Unit& other); // Disallow copy constructor, to prevent leaking of pshape

	sf::Shape * pshape{ nullptr };
	sf::Vector2f velocity{ (float)0.0, (float)0.0 };
};

