#include "MoveComponentGroundBasic.h"
#include "UnitBase.h"
#include "Map.h"
#include <iostream>
#include <SFML/Graphics.hpp>


MoveComponentGroundBasic::MoveComponentGroundBasic(double maxSpeed, double dx_, double dy_) :
	MoveComponent(maxSpeed), dx(dx_), dy(dy_)
{
}


MoveComponentGroundBasic::~MoveComponentGroundBasic()
{
}



// TODO: Get rid of this; replace with the concept of an Order that calls "move()" method on this component when necessary.
void MoveComponentGroundBasic::Update(GameState & gs, unsigned long nTick)
{
	m_parent->x += dx;
	m_parent->y += dy;
}


void MoveComponentGroundBasic::Move(GameState &gs, Point ptDest )
{
	// Move by it's max speed towards the destination, if it's not already close to the destination.
	if (!AtDestination(ptDest))
	{
		Point ptCurrent(m_parent->x, m_parent->y);
		if (ptCurrent.Distance(ptDest) < m_speed)
		{
			// We can move the entire distance this tick
			m_parent->x = ptDest.x;
			m_parent->y = ptDest.y;
		}
		else
		{
			dx = ptDest.x - m_parent->x;
			dy = ptDest.y - m_parent->y;
			CapAtMax( dx, dy)
		}
	}
}


void MoveComponentGroundBasic::Render(GameState & gs, Map &map)
{
	sf::CircleShape * ps = new sf::CircleShape(4.0f);
	ps->setFillColor(sf::Color::Red);
	ps->setPosition((float)(m_parent->x), (float)(m_parent->y));
	ps->setOrigin(4.f, 4.f); // The center of the object rather than the top-left.
	map.GetWindow()->draw(*ps);
	delete ps;
}


// Non-member function; find a better place for this utility function!!!
void CapAtMax( double &dx, double &dy, double max )
{
	double maxsquared = max * max;
	double lengthsquared = dx*dx + dy*dy;
	if (lengthsquared > maxsquared)
	{
		double factor = max / sqrt(lengthsquared);
		dx *= factor;
		dy *= factor;
	}
}

void MoveComponentGroundBasic::SetSpeed(double dx_, double dy_)
{
	CapAtMax(dx_, dy_, m_speed);
	dx = dx_;
	dy = dy_;
}