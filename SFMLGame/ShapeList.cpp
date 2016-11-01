#include "stdafx.h"
#include "ShapeList.h"

using namespace std;

ShapeList::ShapeList()
{
	sf::CircleShape * ps = new sf::CircleShape(100.f);
	ps->setFillColor(sf::Color::Magenta);
	shared_ptr<Unit> pUnit(new Unit(ps, sf::Vector2f(0.2f, 0.2f)));
	AddUnit(pUnit);

	ps = new sf::CircleShape(30.f);
	ps->setFillColor(sf::Color(250, 50, 50));
	ps->setPosition(50.f, 30.f);
	pUnit = make_shared<Unit>(ps, sf::Vector2f(-0.6f, 0.3f));
	AddUnit(pUnit);
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

				if ((sz.top + sz.height) >= wsize.y && vel.y > 0.f )
					vel.y = -vel.y;
				else if (sz.top <= 0 && vel.y < 0.f )
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


void ShapeList::render(shared_ptr<sf::RenderWindow> pwindow )
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
	for(auto it = m_units.begin(); it != m_units.end(); /* do not increment in the loop */ )
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
	
	return( bWasDeleted );
}
