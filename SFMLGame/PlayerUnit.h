#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <list>

// TODO: Move all these and shield functionality to a new shield class?  Or at least inside the PlayerUnit class to control scope...
static const unsigned int MaxShieldPower{ 1000 };	// Max amount of power the player can have.
static const unsigned int ShieldPowerPerTick{ 5 };	// Amount of power the shield uses per tick
static const unsigned int ShieldRechargePerTick{ 1 };	// Amount of power that is charged per tick when the shield is off
static const unsigned int MinShieldPowerToStartShield{ 250 }; // If shield is off, this is the minimum power needed to start the shield.  Prevents shield flicker.

struct Bullet
{
	sf::Vector2f pos; // current position
	sf::Vector2f vel; // velocity
	unsigned int ticksRemaining; // how many ticks remain before the bullet decays.  (This could change to a Time value).
};

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
	const unsigned int getShot() { return(unitsShot); };
	const unsigned int getScore() { return(score); };
	const unsigned int getPower() { return(power); };
	void gainHealth(const unsigned int points);
	bool isAlive() { return(health > 0); };
	bool AreBullets() { return(m_bullets.size() > 0); };
	unsigned int CheckBulletHit(sf::Vector2f pos, float radius);
	unsigned int GetBulletDamage() { return(bulletDamage); };
	void ShotAndDestroyedUnit( unsigned int points );


protected:
	void UpdateShield();
	void UpdateFiring();
	void Fire();
	void MoveBullets(shared_ptr<sf::RenderWindow>, float speedFactor );
	void RenderBullets(shared_ptr<sf::RenderWindow> pwin);
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
	unsigned int power{ MaxShieldPower }; // Shield power, from 0 to 1000.

	// Firing
	sf::Clock lastShotClock;
	sf::Time shotCooldownTime{ sf::milliseconds(150) };
	list<Bullet> m_bullets;
	const float bulletSpeed{ 3.0f };
	const unsigned int maxBulletTicks{ 200 };
	const unsigned int bulletDamage{ 10 };
	unsigned int unitsShot{ 0 };
	unsigned int score { 0 };
};

