#include "stdafx.h"
#include <random>
#include "ShapeList.h"
#include "BadUnit.h"
#include "SuperBad.h"
#include "PlayerUnit.h"
#include "VectorUtils.h"

using namespace std;

ShapeList::ShapeList()
{
	randomGenerator.seed(rd()); // use random_device to seed the random generator from the operating system 
	CreateInitialUnits();
}


ShapeList::~ShapeList()
{
}


void ShapeList::CreateInitialUnits()
{
	// This would be somewhat better because it's more efficient (Unit and shared_ptr control block are allocated as one memory block)
	// and it doesn't risk problems with the raw pointer.
	auto pu1 = make_shared<Unit>(new sf::CircleShape(100.f), sf::Vector2f(0.2f, 0.2f));
	(*pu1).getShape()->setFillColor(sf::Color::Magenta);
	(*pu1).getShape()->setOrigin(100.f, 100.f); // The center of the object rather than the top-left.
	AddUnit(pu1);

	/*  Not as good because unit and shared_ptr control block are allocated separately, and it risks having a raw pointer around.
	sf::CircleShape * ps = new sf::CircleShape(100.f);
	ps->setFillColor(sf::Color::Magenta);
	ps->setOrigin(100.f, 100.f); // The center of the object rather than the top-left.
	shared_ptr<Unit> pUnit(new Unit(ps, sf::Vector2f(0.2f, 0.2f)));
	*/

	shared_ptr<Unit> pu = make_shared<BadUnit>(sf::Vector2f(100.f, 50.f), sf::Vector2f(0.5f, 0.7f), BadUnit::GetDefaults());
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(200.f, 250.f), sf::Vector2f(-0.2f, -0.3f), BadUnit::GetDefaults());
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(30.f, 300.f), sf::Vector2f(0.2f, -0.6f), BadUnit::GetDefaults());
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(350.f, 40.f), sf::Vector2f(-0.6f, 0.6f), BadUnit::GetDefaults());
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(300.f, 50.f), sf::Vector2f(0.3f, -0.5f), BadUnit::GetDefaults());
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(100.f, 400.f), sf::Vector2f(-0.5f, 0.3f), BadUnit::GetDefaults());
	AddUnit(pu);
	pu = make_shared<Unit>(sf::Vector2f(180.f, 20.f), sf::Vector2f(0.2f, 0.2f), nullptr);
	AddUnit(pu);
	pu = make_shared<Unit>(sf::Vector2f(50.f, 30.f), sf::Vector2f(-0.6f, 0.3f), nullptr);
	AddUnit(pu);
	pu = make_shared<SuperBad>(sf::Vector2f(600.f, 500.f), sf::Vector2f(-0.4f, 0.1f), SuperBad::GetDefaults());
	AddUnit(pu);
	pu = make_shared<SuperBad>(sf::Vector2f(400.f, 600.f), sf::Vector2f(-0.6f, -0.7f), SuperBad::GetDefaults());
	AddUnit(pu);
}


// Called on each move... May create new random units
// This would eventually be some function of the length of time the player has been alive, the number of points they've
// accumulated, etc.
// This will be called approximately 100 times per second.
void ShapeList::SpawnUnits( shared_ptr<sf::RenderWindow> pwin )
{
	sf::Time timeSinceLastSpawn = spawnClock.getElapsedTime(); // since the clock was last restarted
	const sf::Time spawnTime{ sf::seconds(1) };
	const sf::Time spawnTimeMax{ sf::seconds(4) };

	// TODO: Update this to not use magic numbers, etc...
	if (m_units.size() < 10 && timeSinceLastSpawn > spawnTime)
	{
		SpawnUnit( pwin );
	}
	else if (timeSinceLastSpawn > spawnTimeMax)
	{
		// always spawn another ball at least this often.
		SpawnUnit( pwin );
	}
}


void ShapeList::SpawnUnit( shared_ptr<sf::RenderWindow> pwin )
{
	// TODO: consider storing this uniform dist function inside the object?
	std::uniform_real_distribution<double> distribution(0.0, 100.f); // create a uniform distribution function with that range.
	unsigned int percent = static_cast<int>(distribution(randomGenerator));

	// Random position.  Eventually: make them only spawn somewhere along the border.
	sf::Vector2u wsize = pwin->getSize();
	sf::Vector2f pos(( distribution(randomGenerator) * (float)wsize.x ) / 100.f, 
					 ( distribution(randomGenerator) * (float)wsize.y) / 100.f);

	// Random Velocity
	std::uniform_real_distribution<double> velocityDistribution(-1.0f, 1.0f);
	sf::Vector2f vel(velocityDistribution(randomGenerator), velocityDistribution(randomGenerator));

	// Random type of unit
	shared_ptr<Unit> pu{ nullptr };
	if( percent < 75)
	{
		// spawn a unit to be eaten
		pu = make_shared<Unit>(pos, vel, Unit::GetDefaults());
	}
	else if (percent < 90)
	{
		// spawn a BadUnit
		pu = make_shared<Unit>(pos, vel, BadUnit::GetDefaults());
	}
	else if (percent < 95)
	{
		// Spawn a SuperBad
		pu = make_shared<Unit>(pos, vel, Unit::GetDefaults());
	}
	else
	{
		// something else...
	}
	if( pu != nullptr )
	{
		AddUnit(pu);
		spawnClock.restart();
	}
}


void ShapeList::updatePositions(shared_ptr<sf::RenderWindow> pwin, float speedFactor )
{
	for (auto it : m_units)
	{
		sf::Shape * ps = (*it).getShape();
		if (ps)
		{
			(*it).move( speedFactor ); // move the unit

			// If shape has moved outside the bounds of the view, reset its velocity
			sf::FloatRect sz = ps->getGlobalBounds();
			sf::Vector2u wsize = pwin->getSize();
			if ((sz.left + sz.width) > wsize.x || sz.left < 0.f || (sz.top + sz.height) > wsize.y || sz.top < 0.f)
			{
				sf::Vector2f vel = (*it).getVelocity();
				/*
				// No because this doesn't take into account shapes which start with bounding boxes somewhat outside the view.
				if ((sz.left + sz.width) > wsize.x || sz.left < 0)
				{
					vel.x = -vel.x;
				}
				if((sz.top + sz.height) > wsize.y || sz.top < 0 )
					vel.y = -vel.y;
				*/
				if (((sz.left + sz.width) >= wsize.x) && vel.x > 0.f)
					vel.x = -vel.x;
				else if (sz.left <= 0 && vel.x < 0.f)
					vel.x = -vel.x;

				if ((sz.top + sz.height) >= wsize.y && vel.y > 0.f)
					vel.y = -vel.y;
				else if (sz.top <= 0 && vel.y < 0.f)
					vel.y = -vel.y;

				(*it).setVelocity(vel);
			}
		}
		else
		{
			// ERROR!  One of the units has no shape!!!
		}
	}
}


void ShapeList::render(shared_ptr<sf::RenderWindow> pwindow)
{
	for (auto it : m_units)
	{
		pwindow->draw(*(*it).getShape());
	}
}

void ShapeList::AddUnit(shared_ptr<Unit>pUnit)
{
	m_units.push_back(pUnit);
}


// Remove all units which intersect the specified point
bool ShapeList::removeUnitsAt(sf::Vector2f pos)
{
	bool bWasDeleted{ false };
	for (auto it = m_units.begin(); it != m_units.end(); /* do not increment in the loop */)
	{
		sf::Shape * ps = (*it)->getShape();
		sf::FloatRect bbox = ps->getGlobalBounds();
		if (bbox.contains(pos))
		{
			// If shape intersects the point, remove the shape.
			it = m_units.erase(it);
			bWasDeleted = true;
		}
		else
		{
			// increment iterator only if we didn't remove this element
			++it;
		}
	}

	return(bWasDeleted);
}


// Collision-detection between player and other objects, based on (center + radius) rather than bounding box! 
// All shapes are circles, and all should have their origin set to their center (so getPos() returns the center, not the top-left).
// Avoid O(N^2) collision detection (no need to detect collisions between all objects and each other; just need to
// detect collisions between the player(s) and all other objects, which is O(N) ).
void ShapeList::HandleCollisions(PlayerUnit &player)
{
	sf::Vector2f PlayerPos = player.getPos();
	float PlayerSize = player.getRadius();

	for (auto it = begin(m_units); it != end(m_units); ) // Omits the incrememt from here.
	{
		sf::Vector2f UnitPos = (*it)->getShape()->getPosition();
		float UnitSize = (float)((*it)->getShape()->getGlobalBounds().width / 2); // Assumes it's a circle...

		if (VectorLength(PlayerPos, UnitPos) < (PlayerSize + UnitSize))
		{
			// Collision!
			if ((*it)->HandleCollision(player))
			{
				// if HandleCollision returns true, destroy that unit
				it = m_units.erase(it); // returns next element
			}
			else
				++it; // didn't destroy unit
		}
		else
		{
			++it; // Wasn't done in the for loop
		}
	}
}