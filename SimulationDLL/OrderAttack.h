#pragma once
#include "Order.h"
#include "UnitBase.h"

#include <memory>


class OrderAttack :
	public Order
{
public:
	OrderAttack() = delete;
	OrderAttack(shared_ptr<UnitBase> pTarget );
	virtual ~OrderAttack();
	bool Execute(GameState &gs, UnitBase * punit, unsigned long nTick );

private:
	shared_ptr<UnitBase> m_pTarget;
};

