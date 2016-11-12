#pragma once
#include "BadUnit.h"

class SuperBad : public BadUnit
{
public:
	SuperBad() = delete;
	SuperBad(sf::Vector2f pos, sf::Vector2f vel, const UnitDefaults *pdef );
	virtual ~SuperBad() = default;
	// virtual bool SuperBad::HandleCollision(PlayerUnit & player);

	// Static functions:
	static const UnitDefaults *GetDefaults() { return &defaults; }; // returns the SuperBad:: copy of defaults.

private:
	static UnitDefaults const defaults;
};

