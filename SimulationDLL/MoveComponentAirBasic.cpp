#include "MoveComponentAirBasic.h"
#include "UnitBase.h"

MoveComponentAirBasic::MoveComponentAirBasic(double maxSpeed, double dx_, double dy_) :
	MoveComponent(maxSpeed), dx(dx_), dy(dy_)
{
}


MoveComponentAirBasic::~MoveComponentAirBasic()
{
}

// TODO: Get rid of this?
void MoveComponentAirBasic::Update(GameState & gs, unsigned long nTick)
{
	m_parent->x += dx;
	m_parent->y += dy;
}

void MoveComponentAirBasic::Move(GameState &gs, Point ptDest)
{
	// TODO: Implement!
}


void MoveComponentAirBasic::Render(GameState & gs, Map &map)
{
	// TODO:
}