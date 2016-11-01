#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Unit.h"

class ShapeList
{
public:
	ShapeList();
	virtual ~ShapeList();
	void updatePositions(shared_ptr<sf::RenderWindow>, float speedFactor );
	void render(shared_ptr<sf::RenderWindow>);
	void AddUnit(shared_ptr<Unit>);
	bool removeUnitsAt(sf::Vector2f);

private:
	std::vector<shared_ptr<Unit>> m_units;
	
};

