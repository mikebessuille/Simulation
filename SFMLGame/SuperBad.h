#pragma once
#include "BadUnit.h"

class SuperBad : public BadUnit
{
public:
	SuperBad() = delete;
	SuperBad(sf::Vector2f pos, sf::Vector2f vel);
	virtual ~SuperBad() = default;
	virtual bool SuperBad::HandleCollision(PlayerUnit & player);

private:
	static const float default_size;
	static const sf::Color default_colour;
	static const unsigned int default_damage;
};

