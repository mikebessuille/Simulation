#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include "Unit.h"
#include "PlayerUnit.h"

class ShapeList
{
public:
	ShapeList();
	virtual ~ShapeList();
	void SpawnUnits();
	void updatePositions(shared_ptr<sf::RenderWindow>, float speedFactor );
	void render(shared_ptr<sf::RenderWindow>);
	void AddUnit(shared_ptr<Unit>);
	bool removeUnitsAt(sf::Vector2f);
	void HandleCollisions(PlayerUnit &player);

private:
	void CreateInitialUnits();
	void SpawnUnit();

private:
	std::vector<shared_ptr<Unit>> m_units;
	sf::Clock spawnClock; // starts the clock.
	std::random_device rd;
	std::mt19937 randomGenerator;
};

