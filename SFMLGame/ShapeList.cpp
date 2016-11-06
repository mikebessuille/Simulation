#include "stdafx.h"
#include "ShapeList.h"
#include "PlayerUnit.h"
#include "VectorUtils.h"

using namespace std;

ShapeList::ShapeList()
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

	shared_ptr<Unit> pu = make_shared<BadUnit>(sf::Vector2f(100.f, 50.f), sf::Vector2f(0.5f, 0.7f));
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(200.f, 250.f), sf::Vector2f(-0.2f, -0.3f));
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(30.f, 300.f), sf::Vector2f(0.2f, -0.6f));
	AddUnit(pu);
	pu = make_shared<BadUnit>(sf::Vector2f(350.f, 40.f), sf::Vector2f(-0.6f, 0.6f));
	AddUnit(pu);
	pu = make_shared<Unit>(sf::Vector2f(180.f, 20.f), sf::Vector2f(0.2f, 0.2f));
	AddUnit(pu);
	pu = make_shared<Unit>(sf::Vector2f(50.f, 30.f), sf::Vector2f(-0.6f, 0.3f));
	AddUnit(pu);
}


ShapeList::~ShapeList()
{
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
			if ((sz.left + sz.width) > wsize.x || sz.left < 0 || (sz.top + sz.height) > wsize.y || sz.top < 0)
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
		float UnitSize = (*it)->getShape()->getGlobalBounds().width / 2; // Assumes it's a circle...

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