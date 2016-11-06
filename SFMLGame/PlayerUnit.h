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
	float getRadius() { if (bShield) return(radius + shieldSize); else return(radius); }
	bool isShield() { return(bShield); }
	bool damage(const unsigned int dmg);
	void gainHealth(const unsigned int points);
	bool isAlive() { return(health > 0); };

protected:
	void update();
	void renderStats( shared_ptr<sf::RenderWindow> pwin );

private:
	shared_ptr<sf::Shape>ps{ nullptr };
	const float radius{ 25.f }; // Maybe this shouldn't be const?  Size can change over time?
	const float baseSpeed{ 0.8f };
	bool bShield{ false };
	float shieldSize{ 5.f }; // Shield size can change over time?
	unsigned int health{ 100 };
	unsigned int eaten{ 0 };
	unsigned int badCollisions{ 0 };
};

