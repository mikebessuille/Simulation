#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include <random>
#include "Unit.h"
#include "PlayerUnit.h"

class ShapeList
{
public:
	ShapeList();
	virtual ~ShapeList();
	void SpawnUnits( shared_ptr<sf::RenderWindow> pwin );
	void updatePositions(shared_ptr<sf::RenderWindow>, float speedFactor );
	void render(shared_ptr<sf::RenderWindow>);
	void AddUnit(shared_ptr<Unit>);
	bool removeUnitsAt(sf::Vector2f);
	void HandleCollisions(PlayerUnit &player);

private:
	void CreateInitialUnits();
	void SpawnUnit( shared_ptr<sf::RenderWindow> pwin );
	void CleanDeletedList();
	void HandleBulletHits(PlayerUnit &player);


private:
	std::list<shared_ptr<Unit> > m_units; // Use list instead of vector, for fast removal of elements in the middle
	std::list<shared_ptr<Unit> > m_deleted; // List of units which have been deleted and the deletion animations are running.
	sf::Clock spawnClock; // starts the clock.
	std::random_device rd;
	std::mt19937 randomGenerator;
};

