#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Unit.h"

class ShapeList
{
public:
	ShapeList();
	virtual ~ShapeList();
	void updatePositions(shared_ptr<sf::RenderWindow>);
	void render(shared_ptr<sf::RenderWindow>);

private:
	std::vector<shared_ptr<Unit>> m_shapes;
	
};

