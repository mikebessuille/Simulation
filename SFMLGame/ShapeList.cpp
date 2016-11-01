#include "stdafx.h"
#include "ShapeList.h"

using namespace std;

ShapeList::ShapeList()
{
	sf::CircleShape * ps(new sf::CircleShape(100.f));
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


void ShapeList::updatePositions(shared_ptr<sf::RenderWindow> pwin )
{
	sf::Vector2u wsize = pwin->getSize();
	sf::Shape * ps;

	for (auto it : m_shapes)
	{
		ps = (*it).getShape();
		(*it).move();

		// If shape has moved outside the bounds of the view, reset it's position or velocity
		sf::Vector2f pos = ps->getPosition();
		sf::Vector2f vel = (*it).getVelocity();
		if (pos.x > wsize.x || pos.x < 0 || pos.y > wsize.y || pos.y < 0)
		{
			// ps->setPosition(0, 0);
			if (pos.x > wsize.x || pos.x < 0)
				vel.x = -vel.x;
			if (pos.y > wsize.y || pos.y < 0)
				vel.y = -vel.y;
			(*it).setVelocity(vel);
		}
	}
}


void ShapeList::render(shared_ptr<sf::RenderWindow> pwindow )
{
	for (auto it : m_shapes)
	{
		pwindow->draw(*(*it).getShape());
	}
}

void ShapeList::AddUnit(shared_ptr<Unit>pUnit)
{
	m_shapes.push_back(pUnit);
}


// Remove all units which intersect the specified point
bool ShapeList::removeUnitsAt(sf::Vector2f pos)
{
	bool bWasDeleted{ false };
	for(auto it = m_shapes.begin(); it != m_shapes.end(); /* do not increment in the loop */ )
	{
		sf::Shape * ps = (*it)->getShape();
		sf::FloatRect bbox = ps->getGlobalBounds();
		if (bbox.contains(pos))
		{
			// If shape intersects the point, remove the shape.
			it = m_shapes.erase(it);
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
