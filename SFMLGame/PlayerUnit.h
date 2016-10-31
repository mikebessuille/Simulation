#pragma once

#include <SFML\Graphics.hpp>
#include <memory>


class PlayerUnit
{
public:
	PlayerUnit();
	virtual ~PlayerUnit();
	void render(shared_ptr<sf::RenderWindow>);
	void move(shared_ptr<sf::RenderWindow>);

private:
	shared_ptr<sf::Shape>ps{ nullptr };
};

