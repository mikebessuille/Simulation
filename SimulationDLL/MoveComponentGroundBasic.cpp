#include "MoveComponentGroundBasic.h"
#include "UnitBase.h"
#include <iostream>
#include <SFML/Graphics.hpp>


MoveComponentGroundBasic::MoveComponentGroundBasic(double maxSpeed, double dx_, double dy_) :
	MoveComponent(maxSpeed), dx(dx_), dy(dy_)
{
}


MoveComponentGroundBasic::~MoveComponentGroundBasic()
{
}

void MoveComponentGroundBasic::Update(GameState & gs, unsigned long nTick)
{
	m_parent->x += dx;
	m_parent->y += dy;
}

void MoveComponentGroundBasic::Render(GameState & gs)
{
	// Logging - take this out!
	cout << "X: [" << m_parent->x << "]  Y: [" << m_parent->y << "]" << endl;

	// TODO: render to the map
	// Test code for basic rendering:
	// HOW CAN THIS HAVE ACCESSS TO THE MAP???  Map should be global?  Shouldn't be part of GameState...
	// Don't really want to pass it in as a parameter all over the place...
	/*
	sf::CircleShape * ps = new sf::CircleShape(4.0f);
	ps->setFillColor(sf::Color::Red);
	ps->setPosition((float)(10*m_parent->x), (float)(10*m_parent->y));
	ps->setOrigin(4.f, 4.f); // The center of the object rather than the top-left.
	pwindow->draw(*ps);
	delete ps;
	*/
}