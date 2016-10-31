#include "stdafx.h"
#include "ShapeList.h"


ShapeList::ShapeList()
{
	sf::CircleShape * ps(new sf::CircleShape(100.f));
	ps->setFillColor(sf::Color::Magenta);
	shared_ptr<Unit> pUnit(new Unit(ps, sf::Vector2f(0.02f, 0.02f)));
	AddUnit(pUnit);

	ps = new sf::CircleShape(30.f);
	ps->setFillColor(sf::Color(250, 50, 50));
	ps->setPosition(50.f, 30.f);
	pUnit = make_shared<Unit>(ps, sf::Vector2f(-0.01f, 0.04f));
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
	pwindow->clear();
	for (auto it : m_shapes )
		pwindow->draw( *(*it).getShape() );
	pwindow->display();
}

void ShapeList::AddUnit(shared_ptr<Unit>pUnit)
{
	m_shapes.push_back(pUnit);
}
