#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "PlayerUnit.h"

// Keep this outside the class, so that the ShapeList class (factory) can refer to it.
struct UnitDefaults
{
	const float default_size;
	const sf::Color default_colour;
	const unsigned int default_points;
	const unsigned int default_damage;
};

class Unit
{
public:
	Unit() = delete;
	Unit(sf::Shape* ps, sf::Vector2f vel);
	Unit(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef );
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
	virtual void Bounce(PlayerUnit &player);

	// Static functions:
	static const UnitDefaults *GetDefaults() { return &defaults; }; // returns the Unit:: version of defaults.

private:
	// Make these (copy ctor, assignment operator) private, simply because KW doesn't properly detect the C++11 "delete" functionality and will assume the default
	// copy constructor & assignment operators were created, which leads KW to believe there are memory problems.
	// Unit& operator=(Unit rhs); // Disallow assignment operator, to prevent leaking of pshape
	// Unit(const Unit& other); // Disallow copy constructor, to prevent leaking of pshape

private:
	static UnitDefaults const defaults; // Must be public so that the factory can reference it

protected:
	sf::Shape * pshape{ nullptr };
	sf::Vector2f velocity{ (float)0.0, (float)0.0 };
	const UnitDefaults * pdefaults;
};

