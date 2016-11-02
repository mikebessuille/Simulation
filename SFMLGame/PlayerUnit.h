#pragma once

#include <SFML\Graphics.hpp>
#include <memory>


class PlayerUnit
{
public:
	PlayerUnit();
	virtual ~PlayerUnit();
	void render(shared_ptr<sf::RenderWindow>);
	void move(shared_ptr<sf::RenderWindow>, float speedFactor );

	sf::Vector2f getPos() { if (ps) return((*ps).getPosition()); else return(sf::Vector2f(0, 0)); }
	float getRadius() { return(radius); }

private:
	shared_ptr<sf::Shape>ps{ nullptr };
	const float radius{ 25.f };
	const float baseSpeed{ 0.8f };
};

