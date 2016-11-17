#pragma once

#include <SFML\Graphics.hpp>
#include <memory>


class PlayerUnit
{
public:
	PlayerUnit();
	virtual ~PlayerUnit();
	
	void Render(shared_ptr<sf::RenderWindow>);
	void Update(shared_ptr<sf::RenderWindow>, float speedFactor );
	sf::Vector2f getPos() { if (ps) return((*ps).getPosition()); else return(sf::Vector2f(0, 0)); }
	float getRadius() { if (bShield) return(radius + shieldSize); else return(radius); }
	sf::Vector2f getVelocity() { return(velCurrent); };
	bool isShield() { return(bShield); }
	bool damage(const unsigned int dmg);
	const unsigned int getHealth() { return(health); };
	const unsigned int getEaten() { return(eaten); };
	void gainHealth(const unsigned int points);
	bool isAlive() { return(health > 0); };

protected:
	void UpdateShield();
	void UpdateFiring();
	void HandleBulletCollisions( shared_ptr<sf::RenderWindow> pwin );
	void Fire();
	void Move(shared_ptr<sf::RenderWindow>, float speedFactor);


private:
	shared_ptr<sf::Shape>ps{ nullptr };
	const float radius{ 25.f }; // Maybe this shouldn't be const?  Size can change over time?
	unsigned int health{ 100 };
	unsigned int eaten{ 0 };
	unsigned int badCollisions{ 0 };

	// Movement
	const float baseSpeed{ 0.8f };
	sf::Vector2f velCurrent; // Most recent velocity

	// Shield
	bool bShield{ false };
	float shieldSize{ 5.f }; // Shield size can change over time?

	// Firing
	sf::Clock lastShotClock;
	sf::Time shotCooldownTime{ sf::milliseconds(100) };
};

