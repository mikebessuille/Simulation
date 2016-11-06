#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "PlayerUnit.h"

class Unit
{
public:
	Unit(sf::Shape* ps, sf::Vector2f vel); // TODO: Deprecate this ctor!
	Unit(sf::Vector2f pos, sf::Vector2f vel);
	virtual ~Unit();
	// These don't work with KW yet...
	Unit& operator=(Unit rhs) = delete; // Disallow assignment operator, to prevent leaking of pshape
	Unit(const Unit& other) = delete; // Disallow copy constructor, to prevent leaking of pshape

	// These don't work because the base constructor will always call the base implementation of these functions
	//virtual const float def_size() const { return default_size; }; /* returns Unit::default_size */
	//virtual sf::Color def_colour() const { return default_colour; }; /* returns Unit::default_colour */

	sf::Shape * getShape();
	void move( const float speedFactor );
	void setVelocity(const sf::Vector2f vel) { velocity = vel; }
	sf::Vector2f getVelocity() { return velocity; }
	virtual bool HandleCollision(PlayerUnit &player);

private:
	// Make these (copy ctor, assignment operator) private, simply because KW doesn't properly detect the C++11 "delete" functionality and will assume the default
	// copy constructor & assignment operators were created, which leads KW to believe there are memory problems.
	// Unit& operator=(Unit rhs); // Disallow assignment operator, to prevent leaking of pshape
	// Unit(const Unit& other); // Disallow copy constructor, to prevent leaking of pshape
	
	static const float default_size;
	static const sf::Color default_colour;

protected:
	sf::Shape * pshape{ nullptr };
	sf::Vector2f velocity{ (float)0.0, (float)0.0 };
};

