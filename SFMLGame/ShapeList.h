#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class ShapeList
{
public:
	ShapeList();
	virtual ~ShapeList();
	void updatePositions(shared_ptr<sf::RenderWindow>);
	void render(shared_ptr<sf::RenderWindow>);

private:
	std::vector<shared_ptr<sf::Shape>> m_shapes;
	sf::Vector2f speed{ (float)0.02, (float)0.02 };
};

