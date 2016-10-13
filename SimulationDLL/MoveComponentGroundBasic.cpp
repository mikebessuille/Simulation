#include "MoveComponentGroundBasic.h"
#include "UnitBase.h"

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