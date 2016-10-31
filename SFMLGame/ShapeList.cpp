#include "stdafx.h"
#include "ShapeList.h"


ShapeList::ShapeList()
{
	shared_ptr<sf::CircleShape> pshape(new sf::CircleShape(100.f));
	pshape->setFillColor(sf::Color::Magenta);
	m_shapes.push_back(pshape);

	pshape = make_shared<sf::CircleShape>(30.f);
	pshape->setFillColor(sf::Color(250, 50, 50));
	pshape->setPosition(50.f, 30.f);
	m_shapes.push_back(pshape);
}


ShapeList::~ShapeList()
{
}


void ShapeList::updatePositions(shared_ptr<sf::RenderWindow> pwin )
{
	sf::Vector2f pos;
	sf::Vector2f newpos;

	sf::Vector2u wsize = pwin->getSize();

	for (auto it : m_shapes)
	{
		(*it).move(speed);
		pos = (*it).getPosition();
		if (pos.x > wsize.x || pos.x < 0 || pos.y > wsize.y || pos.y < 0 )
			(*it).setPosition(0, 0);
	}
}


void ShapeList::render(shared_ptr<sf::RenderWindow> pwindow )
{
	pwindow->clear();
	for (auto it : m_shapes )
		pwindow->draw( *it );
	pwindow->display();
}