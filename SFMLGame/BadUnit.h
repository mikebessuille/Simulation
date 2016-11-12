#pragma once
#include "Unit.h"
class BadUnit :
	public Unit
{
public:
	BadUnit(sf::Shape* ps, sf::Vector2f vel) = delete;
	BadUnit(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef);
	virtual ~BadUnit() = default;

	// These don't work because the base constructor will always call the base implementation of these functions
	//virtual const float def_size() const { return default_size; /* returns BadUnit::default_size */ };
	//virtual sf::Color def_colour() const { return default_colour; /* returns BadUnit::default_colour */ };

	virtual bool HandleCollision(PlayerUnit & player);

	// Static functions:
	static const UnitDefaults *GetDefaults() { return &defaults; }; // returns the BadUnit:: version of defaults.

private:
	static UnitDefaults const defaults;
};

